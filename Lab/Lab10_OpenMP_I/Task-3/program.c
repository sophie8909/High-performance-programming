#include <stdio.h>
#include <omp.h>

void thread_func() {
  int thread_id = omp_get_thread_num();
  int thread_count = omp_get_num_threads();
  printf("This is inside thread_func()!\n");
  printf("Thread %d of %d\n", thread_id, thread_count);
}

int main(int argc, char** argv) {

  int max_threads = omp_get_max_threads();
  printf("Max threads: %d\n", max_threads);
#pragma omp parallel num_threads(12)
  {
    thread_func();
  }

  return 0;
}
