#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "tangents.h"

extern double input;
extern pthread_mutex_t mutex;
extern void* Receive(void* input);
extern void* Calculate(void* input);

double arr[1000000];

int main() {
  FillArray(arr);
  // // declare threads
  // pthread_t receiver;    // to ask the user input
  // pthread_t calculator;  // to calculate the arcsines

  // // initialize mutex
  // if (pthread_mutex_init(&mutex, NULL) != EXIT_SUCCESS) {
  //   perror("Failed to initialize mutex.");
  //   exit(EXIT_FAILURE);
  // }

  // // create the threads
  // pthread_create(&receiver, NULL, Receive, (void*)&input);
  // pthread_create(&calculator, NULL, Calculate, (void*)&input);

  // pthread_join(receiver, NULL);
  // pthread_join(calculator, NULL);

  // pthread_mutex_destroy(&mutex);

  return 0;
}