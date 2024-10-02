#include "square_root.h"

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Array to store data read from "data.txt" by the reader thread. Will contain
 * 10,000 pseudo-randm unsigned integer elements.
 */
unsigned int input_buffer[10000];

/**
 * Global integer variable to indicate how many values the reader thread has
 * read from the "data.txt" file.
 */
unsigned int n_read_values;

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

void *Read(void *param) {
  // read the data.txt file
  FILE *addr_file;
  addr_file = fopen("data.txt", "r");

  for (n_read_values = 0; n_read_values < 10000; n_read_values++) {
    fscanf(addr_file, "%d", &input_buffer[n_read_values]);
  }

  fclose(addr_file);
}