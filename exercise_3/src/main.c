#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "square_root.h"

// extern pthread_mutex_t mutex;
extern void* CheckExists(void* param);

int main() {
  // declare first thread
  pthread_t check_exists;  // to check if data.txt exists

  //   // initialize mutex
  //   if (pthread_mutex_init(&mutex, NULL) != EXIT_SUCCESS) {
  //     perror("Failed to initialize mutex.");
  //     exit(EXIT_FAILURE);
  //   }

  // create the threads
  pthread_create(&check_exists, NULL, CheckExists, NULL);

  // return value for check_exists
  int* data_existed;  // 0 or 1

  pthread_join(check_exists, (void**)&data_existed);

  // pthread_mutex_destroy(&mutex);

  // tests
  printf("%d\n", *data_existed);

  return 0;
}
