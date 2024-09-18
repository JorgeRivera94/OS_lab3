#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

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

int main() {
  // create the threads and their attribtes
  // declare threads and attributes
  //  thread that asks the user for a floating point number between 0 and 1
  pthread_t receiver;    // to ask the user input
  pthread_t calculator;  // to calculate the arcsine
  // pthread_attr_t attr;  // thread attributes

  // asking the user for input number
  double input;

  // create the threads
  pthread_create(
      &receiver, NULL, Receive,
      (void *)&input);  // sync para que calculator no corra hasta tener input y
                        // receiver no corra hasta que calculator imprima
  pthread_create(&calculator, NULL, Calculate, (void *)&input);

  // check if input is greater than 10 to terminate both threads and program
  if (input > 100) {
    printf("Terminating.");
    exit(0);
  }
}