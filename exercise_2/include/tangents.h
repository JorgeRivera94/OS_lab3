#ifndef TANGENTS_H
#define TANGENTS_H

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

extern double arr[1000000];
extern double sum;
void FillArray(double arr[1000000]);  // IN RADIANS
void* CalculateSum(void* sub_array);
void CreateSubArrays(double* sub_array, int starting_index);
void SumAll(double* sum, double* partial_sum);

#endif  // TANGENTS_H