#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

void* Receive(void* input);
void* Calculate(void* input);

extern double input;
extern pthread_mutex_t mutex;
extern pthread_cond_t cond_wait_receive;
extern pthread_cond_t cond_wait_calculate;

#endif  // THREADS_H