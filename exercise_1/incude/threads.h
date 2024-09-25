#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * @brief Asks the user to input a number between 1 and 10
 *
 * @param input
 * @return void*
 */
extern void* Receive(void* input);

/**
 * @brief TODO
 *
 * @param input
 * @return void*
 */
extern void* Calculate(void* input);

/**
 * @brief Global value to store the user provided number.
 */
extern int input;

/**
 * @brief TODO Mutex to control access to input variable.
 *
 */
extern pthread_mutex_t mutex;