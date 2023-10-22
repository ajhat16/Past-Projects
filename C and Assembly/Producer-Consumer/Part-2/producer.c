/* Name: Alex Hatoum
 * X500: hatou003
 * Assignment: #3 Part 2 - Producer
 * CSE-Lab Machines Used:
 *     atlas.cselabs.umn.edu
 */

#include "part2.h"

// Globals for tracking the log file and shared memory
FILE* fp;
Sync *sync_ptr;

/**
 * @brief This function is the producer thread code that the 3 producer
 * processes share. They randomly choose the turn order, then write a message to
 * the buffer and their corresponding files containing the color, the sequence
 * number, and the timestamp it was written at.
 * @param arg The color of the thread passed in as a void *
 */
void *producer (void *arg) {
    int i;

    // Color of the thread is passed in as an argument
    char *prod_color = arg;

    // Caluclate the turn order
    int turn = sync_ptr->turn_calc;
    sync_ptr->turn_calc = (sync_ptr->turn_calc + 1) % 3;

    for (i = 0; i < sync_ptr->num_items; i++) {
        // Begin critical section
        pthread_mutex_lock(&sync_ptr->lock);

        // Wait until it is this thread's turn
        while (turn != sync_ptr->turn_count)
            while(pthread_cond_wait(&sync_ptr->TurnToWrite, &sync_ptr->lock) != 0);

        // Wait until buffer has space available
        while (sync_ptr->count == sync_ptr->N)
            while (pthread_cond_wait(&sync_ptr->SpaceAvailable, &sync_ptr->lock) != 0);

        // Begin formatting message in buffer
        sync_ptr->Buffer[sync_ptr->in].seq_num = i;
        gettimeofday(&sync_ptr->tv, 0);
        sprintf(sync_ptr->Buffer[sync_ptr->in].timestamp, "%ld-%ld", sync_ptr->tv.tv_sec, sync_ptr->tv.tv_usec);
        strcpy(sync_ptr->Buffer[sync_ptr->in].color, prod_color);

        // Write to the buffer with the format depending on the color of the thread
        if (!strcmp(prod_color, "red")) {
            fprintf(fp, "%-4s %-4d %s\n", sync_ptr->Buffer[sync_ptr->in].color, sync_ptr->Buffer[sync_ptr->in].seq_num, sync_ptr->Buffer[sync_ptr->in].timestamp);
        } else if (!strcmp(prod_color, "white")) {
            fprintf(fp, "%-6s %-4d %s\n", sync_ptr->Buffer[sync_ptr->in].color, sync_ptr->Buffer[sync_ptr->in].seq_num, sync_ptr->Buffer[sync_ptr->in].timestamp);
        } else if (!strcmp(prod_color, "blue")) {
            fprintf(fp, "%-4s %-4d %s\n", sync_ptr->Buffer[sync_ptr->in].color, sync_ptr->Buffer[sync_ptr->in].seq_num, sync_ptr->Buffer[sync_ptr->in].timestamp);
        }
        
        // Increment the turn to move to the next thread
        sync_ptr->turn_count = (sync_ptr->turn_count + 1) % 3;

        // Increment the input and count
        sync_ptr->in = (sync_ptr->in + 1) % sync_ptr->N;
        sync_ptr->count++;

        // End of critical section
        pthread_mutex_unlock(&sync_ptr->lock);
        pthread_cond_signal(&sync_ptr->ItemAvailable);
        pthread_cond_broadcast(&sync_ptr->TurnToWrite);
    }

    // Begin critical section
    pthread_mutex_lock (&sync_ptr->lock);

    // Threads wait their turn
    while (turn != sync_ptr->turn_count)
        while(pthread_cond_wait(&sync_ptr->TurnToWrite, &sync_ptr->lock) != 0);

    // Wait until buffer has space available
    while (sync_ptr->count == sync_ptr->N)
        while (pthread_cond_wait(&sync_ptr->SpaceAvailable, &sync_ptr->lock) != 0);

    // Write -1 to the buffer indicating that the producers have finished
    sync_ptr->Buffer[sync_ptr->in].seq_num = -1;
    sync_ptr->in = (sync_ptr->in + 1) % sync_ptr->N;
    sync_ptr->count++;
    sync_ptr->turn_count = (sync_ptr->turn_count + 1) % 3;

    // End critical section
    pthread_mutex_unlock(&sync_ptr->lock);
    pthread_cond_signal(&sync_ptr->ItemAvailable);
    pthread_cond_broadcast(&sync_ptr->TurnToWrite);
}

/**
 * @brief This is the main function for the program. This function sets up the
 * shared memory access for the producer.c file through its command line
 * arguments. It also receives the color of the producer throught the arguments.
 * @param argc The number of arguments provided. This is always at least 1
 * because the executable name is always the first argument.
 * @param argv A char* array of all arguments given in the command line. The
 * first element is always the executable name.
 */
int main(int argc, char *argv[]) {

    // The ID and address pointer for the shared memory
    int id;
    int *ptr;

    // Get the shared memory ID
    if ((id = shmget(atoi(argv[1]), 0, 0)) == -1) {
        perror("Producer shmget failed");
        exit(1);
    }

    // ptr now points to the shared memory space
    if ((ptr = shmat(id, (void *) NULL, 1023)) == (void *) -1) {
        perror("Producer shmat failed");
        exit(1);
    }

    // Casting ptr as a Sync pointer so it can access the struct's elements in
    // the shared memory
    sync_ptr = (Sync *) ptr;

    // Create the filename from the color
    char filename[20];
    sprintf(filename, "producer_%s.log", argv[2]);

    // Open the file
    fp = fopen(filename, "w");

    // Call producer to begin putting items into the buffer
    producer(argv[2]);
}