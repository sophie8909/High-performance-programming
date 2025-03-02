#include <stdio.h>
#include <omp.h>

typedef struct DataForThread {
  double A;
  double B;
  int x;
  int y;
  double result;  // New field to store the computation result
} DataForThread_t;

void thread_func(DataForThread_t* p) {
  printf("Thread %d executing thread_func()!\n", omp_get_thread_num());
  printf("A = %f, B = %f, x = %d, y = %d\n", p->A, p->B, p->x, p->y);

  // Perform some computation and store the result
  p->result = p->A * p->B;  // Example computation: multiply A and B
}

int main(int argc, char** argv) {

  const int nThreads = 2;
  DataForThread_t arr[nThreads];

  /* Prepare data for thread 0. */
  arr[0].A = 3.7;
  arr[0].B = 1.2;
  arr[0].x = 88;
  arr[0].y = 77;

  /* Prepare data for thread 1. */
  arr[1].A = 2.2;
  arr[1].B = 8.8;
  arr[1].x = 444;
  arr[1].y = 555;

#pragma omp parallel num_threads(nThreads)
  {
    /* Get the thread ID */
    int id = omp_get_thread_num();

    /* Call thread_func and give it a pointer to arr[id] */
    thread_func(&arr[id]);
  }

  // Print the computed results after the parallel block
  printf("\nResults after parallel execution:\n");
  printf("Thread 0 result: %f\n", arr[0].result);
  printf("Thread 1 result: %f\n", arr[1].result);

  return 0;
}
