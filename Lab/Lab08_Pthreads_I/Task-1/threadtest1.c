#include <stdio.h>
#include <pthread.h>

void* the_thread_func(void* arg) {
  /* Do something here? */
  printf("the_thread_func() starting doing some work.\n");
  long int i;
  double sum;
  for(i = 0; i < 9000000000; i++)
    sum += 1e-7;
  printf("Result of work in the_thread_func(): sum = %f\n", sum);
  return NULL;
}

void* the_thread_func2(void* arg) {
  /* Do something here? */
  printf("the_thread_func2() starting doing some work.\n");
  long int i;
  double sum;
  for(i = 0; i < 9000000000; i++)
    sum += 1e-7;
  printf("Result of work in the_thread_func2(): sum = %f\n", sum);
  return NULL;
}

int main() {
  printf("This is the main() function starting.\n");

  /* Start thread. */
  pthread_t thread;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread, NULL, the_thread_func, NULL);

  printf("This is the main() function after pthread_create()\n");

  pthread_t thread2;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread2, NULL, the_thread_func2, NULL);

  printf("This is the main() function after pthread_create()\n");


  /* Do something here? */
  printf("main() starting doing some work.\n");
  long int i;
  double sum;
  for(i = 0; i < 9000000000; i++)
    sum += 1e-7;
  printf("Result of work in main(): sum = %f\n", sum);

  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  pthread_join(thread, NULL);
  pthread_join(thread2, NULL);

  return 0;
}
