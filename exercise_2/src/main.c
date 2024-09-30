#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "tangents.h"

extern double arr[1000000];
extern double sum;
extern void* CalculateSum(void* sub_array);

// to measure time
struct timespec thread_start;
struct timespec thread_end;
struct timespec main_start;
struct timespec main_end;

int main() {
  // fill array with tangents of integers from 1 to 1,000,000
  FillArray(arr);

  // Here starts the process using threads
  clock_gettime(CLOCK_MONOTONIC, &thread_start);

  // declare threads
  pthread_t section_1;
  pthread_t section_2;
  pthread_t section_3;
  pthread_t section_4;
  pthread_t section_5;

  // initialize starting index values
  int start_1 = 0;
  int start_2 = start_1 + 200000;
  int start_3 = start_2 + 200000;
  int start_4 = start_3 + 200000;
  int start_5 = start_4 + 200000;

  // subarrays
  double sa_1[200000];
  double sa_2[200000];
  double sa_3[200000];
  double sa_4[200000];
  double sa_5[200000];

  CreateSubArrays(sa_1, start_1);
  CreateSubArrays(sa_2, start_2);
  CreateSubArrays(sa_3, start_3);
  CreateSubArrays(sa_4, start_4);
  CreateSubArrays(sa_5, start_5);

  // declare sum addresses
  double* addr_sum_1;
  double* addr_sum_2;
  double* addr_sum_3;
  double* addr_sum_4;
  double* addr_sum_5;

  // create the threads
  pthread_create(&section_1, NULL, CalculateSum, (void*)&sa_1);
  pthread_create(&section_2, NULL, CalculateSum, (void*)&sa_2);
  pthread_create(&section_3, NULL, CalculateSum, (void*)&sa_3);
  pthread_create(&section_4, NULL, CalculateSum, (void*)&sa_4);
  pthread_create(&section_5, NULL, CalculateSum, (void*)&sa_5);

  pthread_join(section_1, (void**)&addr_sum_1);
  pthread_join(section_2, (void**)&addr_sum_2);
  pthread_join(section_3, (void**)&addr_sum_3);
  pthread_join(section_4, (void**)&addr_sum_4);
  pthread_join(section_5, (void**)&addr_sum_5);

  // sum all partial sums
  SumAll(&sum, addr_sum_1);
  SumAll(&sum, addr_sum_2);
  SumAll(&sum, addr_sum_3);
  SumAll(&sum, addr_sum_4);
  SumAll(&sum, addr_sum_5);

  // test
  printf("Sum is %lf using five threads.\n", sum);

  // End of threads process
  clock_gettime(CLOCK_MONOTONIC, &thread_end);

  // pthread_mutex_destroy(&mutex);

  double main_sum = 0.0;
  // Start of process in main only
  clock_gettime(CLOCK_MONOTONIC, &main_start);

  for (int i = 0; i < 1000000; i++) {
    main_sum += arr[i];
  }
  printf("Sum is %lf using no threads.\n", main_sum);

  // End of process in main only
  clock_gettime(CLOCK_MONOTONIC, &main_end);

  // calculate and print elapsed time
  double thread_elapsed = (thread_end.tv_sec - thread_start.tv_sec) +
                          (thread_end.tv_nsec - thread_start.tv_nsec) / 1e9;
  double main_elapsed = (main_end.tv_sec - main_start.tv_sec) +
                        (main_end.tv_nsec - main_start.tv_nsec) / 1e9;
  printf(
      "The process using five threads, after declarations and filling the "
      "array, took %lfs.\n",
      thread_elapsed);
  printf(
      "The process using no threads, after declarations and filling the array, "
      "took %lfs.\n",
      main_elapsed);

  return 0;
}