#include "threads.h"

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void *Receive(void *input);
void *Calculate(void *input);

void *Receive(void *input) {
  double *n = (double *)input;
  // ask the user for a floating point number
  printf("Enter a number between 0 and 1: ");
  scanf("%lf", &*n);
  printf("\n");

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