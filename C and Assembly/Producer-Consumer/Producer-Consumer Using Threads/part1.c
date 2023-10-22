/* Name: Alex Hatoum
 * X500: hatou003
 * Assignment: #3 Part 1
 * CSE-Lab Machines Used:
 *     atlas.cselabs.umn.edu
 */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

// Struct declaration for the message we are writing
struct message {
    int seq_num;
    char color[6];
    char timestamp[25];
};

// Buffer storing our messages from the producers
struct message Buffer[5];
const int N = 5;

// Tracker for the input and output indices
int in = 0;
int out = 0;

// Counter for the number of items in the buffer
int count = 0;
int num_items = 100;

// Calculations for the turn order of the colored threads
int turn_count = 0;
int turn_calc = 0;

struct timeval tv;

FILE* fp_red = NULL;
FILE* fp_white = NULL;
FILE* fp_blue = NULL;
FILE* fp_consumer = NULL;

pthread_mutex_t  lock;
pthread_cond_t  SpaceAvailable, ItemAvailable, TurnToWrite;

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
    int turn = turn_calc;
    turn_calc = (turn_calc + 1) % 3;

    for (i = 0; i < num_items; i++) {
        // Begin critical section
        pthread_mutex_lock(&lock);

        // Wait until it is this thread's turn
        while (turn != turn_count)
            while(pthread_cond_wait(&TurnToWrite, &lock) != 0);

        // Wait until buffer has space available
        while (count == N)
            while (pthread_cond_wait(&SpaceAvailable, &lock) != 0);

        // Begin formatting message in buffer
        Buffer[in].seq_num = i;
        gettimeofday(&tv, 0);
        sprintf(Buffer[in].timestamp, "%ld-%ld", tv.tv_sec, tv.tv_usec);
        strcpy(Buffer[in].color, arg);

        // Write to the buffer with the format depending on the color of the thread
        if (!strcmp(prod_color, "red")) {
            fprintf(fp_red, "%-4s %-4d %s\n", Buffer[in].color, Buffer[in].seq_num, Buffer[in].timestamp);
        } else if (!strcmp(prod_color, "white")) {
            fprintf(fp_white, "%-6s %-4d %s\n", Buffer[in].color, Buffer[in].seq_num, Buffer[in].timestamp);
        } else if (!strcmp(prod_color, "blue")) {
            fprintf(fp_blue, "%-4s %-4d %s\n", Buffer[in].color, Buffer[in].seq_num, Buffer[in].timestamp);
        }
        
        // Increment the turn to move to the next thread
        turn_count = (turn_count + 1) % 3;

        // Increment the input and count
        in = (in + 1) % N;
        count++;

        // End of critical section
        pthread_mutex_unlock (&lock);
        pthread_cond_signal(&ItemAvailable);
        pthread_cond_broadcast(&TurnToWrite);
    }

    // Begin critical section
    pthread_mutex_lock (&lock);

    // Threads wait their turn
    while (turn != turn_count)
        while(pthread_cond_wait(&TurnToWrite, &lock) != 0);

    // Wait until buffer has space available
    while (count == N)
        while (pthread_cond_wait(&SpaceAvailable, &lock) != 0);

    // Write -1 to the buffer indicating that the producers have finished
    Buffer[in].seq_num = -1;
    in = (in + 1) % N;
    count++;
    turn_count = (turn_count + 1) % 3;

    // End critical section
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&ItemAvailable);
    pthread_cond_broadcast(&TurnToWrite);
}

/**
 * @brief The consumer process for the buffer the producers write to. This
 * function checks if the buffer is full, and removes items from the buffer if
 * it is full. The consumer ends when it reads -1 from the buffer.
 * @param arg Nothing is stored in this variable.
 */
void *consumer (void *arg) {
    struct message i;

    i.seq_num = 0;
    do {
        // Begin critical section
        pthread_mutex_lock (&lock);

        // Wait if the buffer is empty
        while (count == 0)
            while (pthread_cond_wait( &ItemAvailable, &lock) != 0);

        // Check to make sure the buffer is not empty
        if (count > 0) {
            // Remove item
            i = Buffer[out];

            // If the number is not -1, write to the consumer file
            if (i.seq_num != -1) {
                gettimeofday(&tv, 0);
                fprintf(fp_consumer, "%-7s %-7d %-19s %ld-%ld\n", i.color, i.seq_num, i.timestamp, tv.tv_sec, tv.tv_usec);
                out = (out + 1) % N; 
                count--;
            }
        }

        // End critical section
        pthread_mutex_unlock (&lock);
        pthread_cond_signal(&SpaceAvailable);

    // Check if the sequence number is -1
    } while (i.seq_num != -1);
}

/**
 * @brief The main function for this program. This function is responsible for
 * creating and terminating the 3 producer and 1 consumer thread. It is also
 * responsible for opening all files used in this program, and initializing the
 * condition and mutex variables.
 * @param argc The number of command line arguments given during execution. By
 * default, this number is 1 because it counts the executable name as an
 * argument.
 * @param argv A char* array of all arguments given in the command line. The
 * first element is always the executable name.
 */
int main(int argc, char* argv[]) {
    
    // Check number of arguments to see if the program was used properly
    if (argc != 2) {
        printf("Usage: %s <number of items for producers to deposit>\n", argv[0]);
        printf("Number of items defaulted to 100.\n");
    } else {
        num_items = atoi(argv[1]);
    }

    // Initialize the producers, consumer, the colors, and a temporary integer
    pthread_t prod[3];
    pthread_t cons;
    int n;
    char* colors[3] = {"red", "white", "blue"};

    // Randomize the order the threads write to the buffer
    srand(time(NULL));
    turn_calc = rand() % 3;

    // Initialize mutex and condition variables
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&SpaceAvailable, NULL);
    pthread_cond_init(&ItemAvailable, NULL);
    pthread_cond_init(&TurnToWrite, NULL);

    // Open producer and consumer files
    fp_red = fopen("producer_red.log", "w");
    fp_white = fopen("producer_white.log", "w");
    fp_blue = fopen("producer_blue.log", "w");

    fp_consumer = fopen("consumer.log", "w");

    // Create the producer threads
    for (int i = 0; i < 3; i++) {
        if (n = pthread_create(&(prod[i]), NULL, producer, colors[i])) {
            fprintf(stderr,"pthread_create :%s\n",strerror(n));
            exit(1); 
        }
    }

    // Create the consumer thread
    if (n = pthread_create(&cons, NULL, consumer, NULL)) {
        fprintf(stderr,"pthread_create :%s\n",strerror(n));
        exit(1);
    }

    // Wait for all producers to finish execution
    for (int i = 0; i < 3; i++) {
        if (n = pthread_join(prod[i], NULL)) {
            fprintf(stderr,"pthread_join:%s\n",strerror(n));
            exit(1);
        }
    }

    // Wait for consumer to finish execution
    if (n = pthread_join(cons, NULL)) { 
        fprintf(stderr,"pthread_join:%s\n",strerror(n));
        exit(1);
    }
    
    // Close all files
    fclose(fp_red);
    fclose(fp_white);
    fclose(fp_blue);
    fclose(fp_consumer);

    printf("Finished execution\n" );

}
