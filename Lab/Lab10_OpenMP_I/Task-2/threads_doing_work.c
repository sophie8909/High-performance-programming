#include <stdio.h>
#include <omp.h>
#include <stdlib.h>


void do_some_work() {
  printf("Now I am going to do some work...\n");
  long int i;
  long int j = 0;
  for(i = 0; i < 3000000000; i++) {
    j += 3;
  }
  printf("Work done! My result j = %ld\n", j);
}

int main(int argc, char** argv) {

  int n = argv[1] ? atoi(argv[1]) : 4;
  printf("Number of threads: %d\n", n);
  double start_time = omp_get_wtime();
#pragma omp parallel num_threads(n)
  {
    do_some_work();
  }
  double end_time = omp_get_wtime();
  printf("Elapsed time: %f\n", end_time - start_time);
  return 0;
}
