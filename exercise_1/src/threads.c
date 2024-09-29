#include "threads.h"

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond_wait_receive;
pthread_cond_t cond_wait_calculate;

/**
 * @brief Asks the user to input a number between 0 and 1.
 *
 * Receives a number from the user and updates a global double variable.
 *
 * @param input void pointer as a thread operates the function. Is type casted
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

// to calculate the arcsine and print it to screen
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