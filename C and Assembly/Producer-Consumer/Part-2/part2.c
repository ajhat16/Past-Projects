/* Name: Alex Hatoum
 * X500: hatou003
 * Assignment: #3 Part 2
 * CSE-Lab Machines Used:
 *     atlas.cselabs.umn.edu
 */

#include "part2.h"

/**
 * @brief This is the main function for the program. This function sets up the
 * shared memory access for the producers and consumer that it creates. It also
 * initializes all of the Sync struct's data members for the shared memory.
 * @param argc The number of arguments provided. This is always at least 1
 * because the executable name is always the first argument.
 * @param argv A char* array of all arguments given in the command line. The
 * first element is always the executable name.
 */
int main(int argc, char *argv[]) {

    Sync sharing;

    // Check command line arguments
    if (argc != 2) {
        printf("Usage: %s <number of items for producers to deposit>\n", argv[0]);
        printf("Number of items defaulted to 100.\n");
        sharing.num_items = 100;
    } else {
        sharing.num_items = atoi(argv[1]);
    }

    // Declare variables for the shared memory
    int shmem_id;
    int *shmem_ptr;
    key_t key;
    int size;
    int flag;

    key = 4455;
    size = sizeof(Sync);
    flag = 1023;

    // Create the shared memory space
    if ((shmem_id = shmget (key, size, flag)) == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Set the pointer to the memory space
    if ((shmem_ptr = shmat (shmem_id, (void *) NULL, flag)) == (void *) -1) {
        perror ("shmat failed");
        exit (2);
    }

    // Cast the pointer as a Sync pointer to allow the shared memory to store
    // struct in part2.h
    Sync *sync_ptr = (Sync *) shmem_ptr;

    // Initialize variables in the Sync struct
    sync_ptr->N = 5;
    sync_ptr->turn_calc = 0;
    sync_ptr->turn_count = 0;
    sync_ptr->in = 0;
    sync_ptr->out = 0;
    sync_ptr->count = 0;
    sync_ptr->num_items = sharing.num_items;

    // Initialize condition and mutex variables for sharing
    pthread_mutexattr_init(&sync_ptr->m_attr);
    pthread_mutexattr_setpshared(&sync_ptr->m_attr, PTHREAD_PROCESS_SHARED);
    pthread_condattr_init(&sync_ptr->c_attr);
    pthread_condattr_setpshared(&sync_ptr->c_attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&sync_ptr->lock, &sync_ptr->m_attr);
    pthread_cond_init(&sync_ptr->SpaceAvailable, &sync_ptr->c_attr);
    pthread_cond_init(&sync_ptr->ItemAvailable, &sync_ptr->c_attr);
    pthread_cond_init(&sync_ptr->TurnToWrite, &sync_ptr->c_attr);

    // Create PID variables for all children
    pid_t pid_red, pid_white, pid_blue, pid_cons;

    // Red child
    if ((pid_red = fork()) == -1) {
        perror("Error making red child");
        exit(1);
    } else if (pid_red == 0) {
        // Prepare the command line arguments for the execl call
        char keystr[10];
        sprintf(keystr, "%d", key);

        // Execute producer code with keystr and red as the arguments
        execl("./producer", "producer", keystr, "red", NULL);
    }

    if ((pid_white = fork()) == -1) {
        perror("Error making white child");
        exit(1);
    } else if (pid_white == 0) {
        // Prepare the command line arguments for the execl call
        char keystr[10];
        sprintf(keystr, "%d", key);

        // Execute producer code with keystr and white as the arguments
        execl("./producer", "producer", keystr, "white", NULL);
    }

    if ((pid_blue = fork()) == -1) {
        perror("Error making blue child");
        exit(1);
    } else if (pid_blue == 0) {
        // Prepare the command line arguments for the execl call
        char keystr[10];
        sprintf(keystr, "%d", key);

        // Execute producer code with keystr and blue as the arguments
        execl("./producer", "producer", keystr, "blue", NULL);
    }

    if ((pid_cons = fork()) == -1) {
        perror("Error making consumer child");
        exit(1);
    } else if (pid_cons == 0) {
        // Prepare the command line arguments for the execl call
        char keystr[10];
        sprintf(keystr, "%d", key);

        // Execute consumer code with keystr as the argument
        execl("./consumer", "consumer", keystr, NULL);
    }

    // Wait for all children to finish
    wait(NULL);

    return 0;

}
