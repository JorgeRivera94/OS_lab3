#include "square_root.h"

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * @brief Array that holds 1,000,000 elements of type double. The elements are
 * the tangents of the numbers [1, 1000000].
 */
double arr[1000000];

/**
 * @brief Variable of type double to hold the sum of all elements in an array
 * containing the tangents of all numbers in the range [1, 1000000].
 */
double sum = 0.0;

/**
 * @brief Takes an array of type double and fills it with the tangents of all
 * numbers in the range [1, 1000000].
 *
 * @param arr Array of type double and size of 1,000,000.
 */
void FillArray(double arr[1000000]) {
  for (int i = 1; i < 1000001; i++) {
    arr[i] = tan((double)i);
  }
}

/**
 * @brief Creates a sub array of size 200,000 and type double of the array
 * containing 1,000,000 double elements.
 *
 * @param sub_array Array of of type double and size 200,000 to be filled with a
 * sub array of type double.
 * @param starting_index Integer starting index on the original array of whom
 * the sub array of 200,000 elements is being created.
 */
void CreateSubArrays(double *sub_array, int starting_index) {
  for (int i = 0; i < 200000; i++) {
    sub_array[i] = arr[i + starting_index];
  }
}

/**
 * @brief Checks if the file "data.txt" exists. If it does not exist, creates
 * the file and writes 10,000 pseudo-random unsigned integer numbers on it.
 *
 * This function is operated by a thread.
 * @param param Unused void pointer.
 * @return void* Void pointer to the address that will the store 0 if the file
 * did not exist, or 1 if the file existed.
 */
void *CheckExists(void *param) {
  int *ans;
  // check if the file exists
  FILE *addr_file;
  addr_file = fopen("data.txt", "r");
  // if the file existed
  if (addr_file != NULL) {
    // fclose(addr_file);
    *ans = 1;
    return (void *)ans;
  } else {
    // if the file did not exist
    addr_file = fopen("data.txt", "w");
    // range of 8bit unsigned int is [0, 255]
    srand(time(NULL));
    for (int i = 0; i < 10000; i++) {
      unsigned int data = rand() % 256;
      fprintf(addr_file, "%d\n", data);
    }
    fclose(addr_file);
    *ans = 0;
    return (void *)ans;
  }
}

/**
 * @brief Updates the total sum with the given partial sum.
 *
 * @param sum Double type pointer to variable holding the sum of all elements in
 * the 1,000,000 element array.
 * @param partial_sum Double type pointer to the sum of the elements of a
 * certain sub array of 200,000 elements.
 */
void SumAll(double *sum, double *partial_sum) {
  // add the partial sums
  *sum += *partial_sum;
}
