/* Name: Alex Hatoum
 * X500: hatou003
 * Assignment: #1
 * CSE-Lab Machines Used:
 *     csel-kh1250-09.cselabs.umn.edu
 *     apollo.cselabs.umn.edu (WARNING: apollo is very slow)
 */

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/prctl.h>

int LIMIT = 0;
int parent_counter = 0;
int child_counter = 0;
int fd;
char buf[1000];

/**
 * @brief Handler for the SIGINT (^C) signal. The parent waits for the child
 * process to exit, then the parent exits.
 */
void SIGINT_handler() {
    wait(NULL);
    close(fd);
    _exit(0);
}

/**
 * @brief Handler for when the child recieves SIGUSR2 (meaning the parent has
 * exited). Stops the child from becoming a zombie process and allows the child
 * to exit gracefully.
 */
void SIGUSR2_child_handler() {
    close(fd);
    _exit(0);
}

/**
 * @brief Handler for when the child exits. The function waits to ensure the
 * child is dead before the parent gracefully terminates.
 */
void SIGCHLD_handler() {
    wait(NULL);
    close(fd);
    _exit(0);
}

/**
 * @brief The handling of SIGUSR2 (the parent function's signal). Writes to the
 * logger file.
 */
void SIGUSR2_handler() {
    signal(SIGUSR2, SIGUSR2_handler);
    sprintf(buf, "Parent %d\n", parent_counter);
    write(fd, buf, strlen(buf));
}
/**
 * @brief The handling of SIGUSR1 (the child function's signal). Writes to the
 * logger file.
*/
void SIGUSR1_handler() {
    signal(SIGUSR1, SIGUSR1_handler);
    sprintf(buf, "Child %d\n", child_counter);
    write(fd, buf, strlen(buf));
}

/**
 * @brief The purpose of this program is to send signals back and forth between
 * a parent and child process. These signals allow a sort of "ping pong" game
 * between the parent and child where they take turns writing to an output file
 * called "Logger" until a limit specified in the command line arguments is
 * reached.
 * @param argc This parameter specifies the number of arguments given in the
 * command line, with the first argument always being the name of the program
 * itself (pingpong).
 * @param argv This is a char* array which contains all command line arguments
 * that were given, with the first argument always being the name of the program
 * (pingpong). The second argument should be an integer limiting the length of
 * the "ping pong" game.
 * @return 0 on successful execution of the program, 1 if there was an error.
 */
int main(int argc, char **argv) {
    // Argument checking; if the number of arguments is not 2, the program exits
    if (argc != 2) {
        fprintf(stderr, "USAGE: %s <LIMIT (integer)>\n", argv[0]);
        exit(0);
    }

    signal(SIGINT, SIGINT_handler);  // Handler for SIGINT

    // Convert the argument to an integer
    LIMIT = atoi(argv[1]);

    // Opening the logger file for writing
    fd = open("Logger", O_CREAT | O_WRONLY | O_TRUNC);

    // Error checking for open() call
    if (fd == -1) {
        perror("File could not be opened");
        exit(1);
    }

    // Creation of the sigset that will be used in the call of sigsuspend later
    sigset_t signal_set;
    sigemptyset(&signal_set);

    // Signal mask declaration and initialization
    sigset_t prevent_deadlock;
    sigemptyset(&prevent_deadlock);

    // Creating a blocking mask to prevent race condition
    sigaddset(&prevent_deadlock, SIGUSR1);
    sigaddset(&prevent_deadlock, SIGUSR2);
    sigprocmask(SIG_BLOCK, &prevent_deadlock, NULL);

    prctl(PR_SET_PDEATHSIG, SIGUSR2); 

    // Storing child's PID in pid during the fork() call
    pid_t pid = fork();

    // Will be used to store the parent's PID
    int ppid = 0;

    if (pid == -1) {  // Error Checking
        perror("Fork failed, no child created");
        exit(1);
    } else if (pid == 0) {  // Child process
        signal(SIGUSR2, SIGUSR2_child_handler);  // Handling for SIGUSR2 (meaning the parent died)
        signal(SIGUSR1, SIGUSR1_handler);  // Handling for SIGUSR1
        ppid = getppid();  // Storing the parent's PID

        while  (child_counter <= LIMIT) {
            sigsuspend(&signal_set);  // Wait for a signal
            if (child_counter == 0) {  // Prints to the terminal on the first iteration
                printf("CHILD::child process executing with LIMIT = %d\n", LIMIT);
                printf("CHILD::child process id = %d\n", getpid());
            }
            kill(ppid, SIGUSR2);  // Send signal to parent
            child_counter++;
        }
    } else {  // Parent process
        // Unblocking the signals for the raise() call below
        sigprocmask(SIG_UNBLOCK, &prevent_deadlock, NULL);
        
        signal(SIGCHLD, SIGCHLD_handler);  // Handling of SIGCHLD
        signal(SIGUSR2, SIGUSR2_handler);  // Handling of SIGUSR2
        raise(SIGUSR2);  // Sending SIGUSR2 to itself so it writes to the file first
        parent_counter++;

        printf("PARENT::parent process executing with LIMIT = %d\n", LIMIT);
        printf("PARENT::parent process id = %d\n", getpid());

        // Re-enabling the block so no deadlocks occur during execution
        sigprocmask(SIG_BLOCK, &prevent_deadlock, NULL);

        while (parent_counter <= LIMIT) {
            kill(pid, SIGUSR1);  // Send signal to child process
            sigsuspend(&signal_set);  // Wait for a signal
            parent_counter++;
        }

        // This is necessary because the parent starts by raising SIGUSR2 to itself
        kill(pid, SIGUSR1);
    }

    wait(NULL);  // Waiting for all children to finish before the parent returns

    close(fd);  // Close file

    return 0;
}
