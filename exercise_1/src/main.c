#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

// global variables and functions from threads.h
int input;
pthread_mutex_t mutex;
void* Receive(void* input);
void* Calculate(void* input);

int main() {
  // declare threads
  pthread_t receiver;    // to ask the user input
  pthread_t calculator;  // to calculate the arcsines

  // initialize mutex
  pthread_mutex_init(&mutex, NULL);

  // create the threads
  pthread_create(&receiver, NULL, Receive, (void*)&input);

  // sync para que calculator no corra hasta tener input y
  // receiver no corra hasta que calculator imprima

  pthread_create(&calculator, NULL, Calculate, (void*)&input);

  // check if input is greater than 10 to terminate both threads and program
  if (input > 100) {
    printf("Terminating.");
    exit(0);
  }
}