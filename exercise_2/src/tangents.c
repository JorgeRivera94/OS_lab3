#include "tangents.h"

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void FillArray(double arr[1000000]) {
  for (int i = 1; i < 1000001; i++) {
    arr[i] = tan((double)i);
  }
}
/**
 * @brief Global value to store the user provided number.
 */
double input;

/**
 * @brief Mutex to control access to input variable by threads receiver and
 * calculator.
 */
pthread_mutex_t mutex;

/**
 * @brief Conditional variable for the thread receiving the input to wait until
 * the calculator thread finishes calculating the arcsine and printng the value.
 */
pthread_cond_t cond_wait_receive;

/**
 * @brief Conditional variable for the thread calculating the arcsine to wait
 * until the receiver thread receives a new value before starting the
 * calculation and printing the result.
 */
pthread_cond_t cond_wait_calculate;

/**
 * @brief Asks the user to input a number between 0 and 1.
 *
 * Receives a number from the user and updates a global double type variable. Is
 * operated by the receiver thread and syncronized with the thread running
 * Calculate() by a shared mutex and conditional wait variables. If the user
 * input is greater than 100, it wakes up the calculator thread, unlucks the
 * mutex, and terminates the receiver thread.
 * @param input Void pointer as a thread operates the function. Is type casted
 * into a double type pointer referencing a global double variable.
 * @return void* Void pointer return as a thread operates the function.
 */
void *Receive(void *input) {
  double *n = (double *)input;

  while (1) {
    // ask the user for a floating point number
    pthread_mutex_lock(&mutex);  // enter and lock

    printf("Enter a number between 0 and 1: ");
    scanf("%lf", &*n);

    if (*n > 100) {
      printf("Number greater than 100 entered. Exiting.\n");
      pthread_cond_signal(&cond_wait_calculate);
      pthread_mutex_unlock(&mutex);
      void *status;
      pthread_exit(status);
    }

    pthread_cond_signal(&cond_wait_calculate);
    pthread_cond_wait(&cond_wait_receive, &mutex);
    pthread_mutex_unlock(&mutex);  // leave and unlock
  }
}

/**
 * @brief Reads the value of a global double type variable representing the user
 * input. If the value is between 0 and 1, calculates the input's arcsine and
 * displays the result.
 *
 * Is operated by the calculator thread and syncronized with the thread running
 * Receive() by a shared mutex and conditional wait variables. If the user
 * input is greater than 100, it wakes up the receiver thread, unlucks the
 * mutex, and terminates the receiver thread.
 * @param input Void pointer to be type casted into a double type pointer.
 * Represents the user input obtained by Receive().
 * @return void* Void pointer as a thread operates the function.
 */
void *Calculate(void *input) {
  double *n = (double *)input;

  while (1) {
    pthread_mutex_lock(&mutex);

    if (*n >= 0 && *n <= 1) {
      // calculate the arcsine
      double arcsine = asin(*n);
      // show it on screen
      printf("The arcsine of %lf is %lf.\n", *n, arcsine);
    } else if (*n > 100) {
      pthread_cond_signal(&cond_wait_receive);
      pthread_mutex_unlock(&mutex);
      void *status;
      pthread_exit(status);
    }

    pthread_cond_signal(&cond_wait_receive);
    pthread_cond_wait(&cond_wait_calculate, &mutex);
    pthread_mutex_unlock(&mutex);
  }
}