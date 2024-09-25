#include "tangent.h"

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

double arr[1000000];

void FillArray(double arr[1000000]) {
  for (int i = 0; i < 1000000; i++) {
    arr[i] = tan((double)i);
  }

  // PRINT DEBUGGING
  printf("%ld", arr);
}