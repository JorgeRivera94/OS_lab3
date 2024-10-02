#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "square_root.h"

extern void* CheckExists(void* param);
extern void* Read(void* param);

int main() {
  // declare threads
  pthread_t check_exists;  // to check if data.txt exists
  pthread_t reader;        // to store the values of data.txt in an array

  // create initial thread
  pthread_create(&check_exists, NULL, CheckExists, NULL);

  // return value for check_exists
  int* data_existed;  // 0 or 1

  pthread_join(check_exists, (void**)&data_existed);

  // second thread
  pthread_create(&reader, NULL, Read, NULL);

  // wait for the second thread to end
  pthread_join(reader, NULL);

  return 0;
}
