/* Name: Alex Hatoum
 * X500: hatou003
 * Assignment: #3 Part 2 - Consumer
 * CSE-Lab Machines Used:
 *     atlas.cselabs.umn.edu
 */

#include "part2.h"

// Globals for shared memory and file access
FILE* fp;
Sync *sync_ptr;

/**
 * @brief The consumer process for the buffer the producers write to. This
 * function checks if the buffer is full, and removes items from the buffer if
 * it is full. The consumer ends when it reads -1 from the buffer.
 * @param arg Nothing is stored in this variable.
 */
void *consumer (void *arg) {
    Message i;

    i.seq_num = 0;
    do {
        // Begin critical section
        pthread_mutex_lock (&sync_ptr->lock);

        // Wait if the buffer is empty
        while (sync_ptr->count == 0)
            while (pthread_cond_wait( &sync_ptr->ItemAvailable, &sync_ptr->lock) != 0);

        // Check to make sure the buffer is not empty
        if (sync_ptr->count > 0) {
            // Remove item
            i = sync_ptr->Buffer[sync_ptr->out];

            // If the number is not -1, write to the consumer file
            if (i.seq_num != -1) {
                gettimeofday(&sync_ptr->tv, 0);
                fprintf(fp, "%-7s %-7d %-19s %ld-%ld\n", i.color, i.seq_num, i.timestamp, sync_ptr->tv.tv_sec, sync_ptr->tv.tv_usec);
                sync_ptr->out = (sync_ptr->out + 1) % sync_ptr->N; 
                sync_ptr->count--;
            }
        }

        // End critical section
        pthread_mutex_unlock (&sync_ptr->lock);
        pthread_cond_signal(&sync_ptr->SpaceAvailable);

    // Check if the sequence number is -1
    } while (i.seq_num != -1);
}

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

    // Open the consumer log file
    fp = fopen("consumer.log", "w");

    // Call consumer to begin the synchronization
    consumer(NULL);
}