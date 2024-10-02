#ifndef SQUARE_ROOT_H
#define SQUARE_ROOT_H

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

extern void* CheckExists(void* param);
extern void* Read(void* param);

extern unsigned int input_buffer[10000];
extern unsigned int n_read_values;

#endif  // SQUARE_ROOT_H