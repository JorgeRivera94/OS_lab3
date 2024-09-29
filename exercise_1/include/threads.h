#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * @brief Asks the user to input a number between 1 and 10
 *
 * @param input
 * @return void*
 */
void* Receive(void* input);

/**
 * @brief TODO
 *
 * @param input
 * @return void*
 */
void* Calculate(void* input);

/**
 * @brief Global value to store the user provided number.
 */
extern double input;

/**
 * @brief TODO Mutex to control access to input variable.
 *
 */
extern pthread_mutex_t mutex;

/**
 * @brief Conditional variable for the thread receiving the input to wait until
 * the calculator thread finishes calculating the arcsine and printng the value.
 *
 */
extern pthread_cond_t cond_wait_receive;

/**
 * @brief Conditional variable for the thread calculating the arcsine to wait
 * until the receiver thread receives a new value before starting the
 * calculation and printing the result.
 *
 */
extern pthread_cond_t cond_wait_calculate;

#endif  // THREADS_H