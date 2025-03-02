/**********************************************************************
 * This program calculates pi using C
 *
 **********************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 1
double partial_sums[NUM_THREADS];  // Store results separately
pthread_t threads[NUM_THREADS];

typedef struct {
  int id;  // Thread ID
} ThreadData;



void* calculate_pi(void* arg) {
  ThreadData* data = (ThreadData*) arg;
  int id = data->id;
  const int intervals = 500000000;
  double sum, dx, x;
  int i;

  dx  = 1.0/intervals;
  sum = 0.0;

  for (i = id; i <= intervals; i+=NUM_THREADS) { 
    x = dx*(i - 0.5);
    sum += dx*4.0/(1.0 + x*x);
  }

  partial_sums[id] = sum;
  return NULL;
}
int main(int argc, char *argv[]) {
  ThreadData data[NUM_THREADS];


  double pi = 0.0;

  // Create threads
  for (int i = 0; i < NUM_THREADS; i++) {
    data[i].id = i;
    pthread_create(&threads[i], NULL, calculate_pi, &data[i]);
  }

  // Wait for threads to finish
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
    pi += partial_sums[i];
  }

  printf("PI is approx. %.16f\n",  pi);

  return 0;
}
