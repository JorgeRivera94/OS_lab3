#include "threads.h"

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// to receive the user input
void *Receive(void *input) {
  double *n = (double *)input;
  while (1) {  // para que siempre lo pida
    // ask the user for a floating point number
    pthread_mutex_lock(&mutex);  // enter and lock
    printf("Enter a number between 0 and 1: ");
    scanf("%lf", &*n);
    printf("\n");
    pthread_mutex_unlock(&mutex);  // leave and unlock
  }

  if (*n > 100) {
    void *status;
    pthread_exit(status);
  }
}

// to calculate the arcsine and print it to screen
void *Calculate(void *input) {  // void* param
  double *n = (double *)input;
  if (*n >= 0 && *n <= 1) {
    // calculate the arcsine
    double arcsine = asin(*n);
    // show it on screen
    printf("The arcsine of %lf is %lf.", *n, arcsine);
  } else if (*n > 100) {
    void *status;
    pthread_exit(status);
  }
}