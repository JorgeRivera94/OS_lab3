#include "tangents.h"

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
 * @brief Calculates the sum of the type double elements of the parameter array.
 *
 * This function is operated by a thread.
 * @param sub_array Void pointer to the parameter sub array whose elements will
 * be summed.
 * @return void* Void pointer to the address that will the store the partial sum
 * obtained by taking the sum of this sub array.
 */
void *CalculateSum(void *sub_array) {
  double *sub_double = (double *)sub_array;
  double sum = 0.0;
  for (int i = 0; i < 200000; i++) {
    sum += sub_double[i];
  }

  double *ptr_sum = malloc(1 * sizeof(double));
  *ptr_sum = sum;

  return (void *)ptr_sum;
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
