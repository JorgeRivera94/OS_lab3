#ifndef TANGENTS_H
#define TANGENTS_H

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

// void* Receive(void* input);
// void* Calculate(void* input);

// extern double input;
// extern pthread_mutex_t mutex;
// extern pthread_cond_t cond_wait_receive;
// extern pthread_cond_t cond_wait_calculate;

extern double arr[1000000];
void FillArray(double arr[1000000]);  // IN RADIANS

#endif  // TANGENTS_H