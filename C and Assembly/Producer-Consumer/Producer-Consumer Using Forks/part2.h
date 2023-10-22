#ifndef PART2_H
#define PART2_H

#include <sys/types.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

// struct synchronization {
//     key_t key;
//     pthread_mutex_t  lock;
//     pthread_cond_t  SpaceAvailable, ItemAvailable, TurnToWrite;
// };



// struct count_items {
//     // struct message Buffer[5];
//     const int N = 5;
//     int in = 0;
//     int out = 0;
//     int count = 0;
//     int num_items = 100;
//     struct timeval tv;
// };

typedef struct message {
    int seq_num;
    char color[6];
    char timestamp[25];
} Message;

typedef struct synchronization {
    Message Buffer[5];
    pthread_mutex_t  lock;
    pthread_cond_t  SpaceAvailable, ItemAvailable, TurnToWrite;
    pthread_mutexattr_t m_attr;
    pthread_condattr_t c_attr;
    int N;
    int turn_calc;
    int turn_count;
    int in;
    int out;
    int count;
    int num_items;
    struct timeval tv;
} Sync;

#endif