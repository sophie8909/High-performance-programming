#include <stdio.h>
#include <pthread.h>

void* the_thread_func(void* arg) {
  /* Do something here? */
  printf("the_thread_func() starting doing some work.\n");
  for(int i = 0; i < 3; i++)
  {
    printf("thread 1: data_for_thread[%d] = %f\n", i, ((double*)arg)[i]);
    ((double*)arg)[i] += 1.0;
  }
  return NULL;
}

void* the_thread_func2(void* arg) {
  /* Do something here? */
  printf("the_thread_func2() starting doing some work.\n");
  for(int i = 0; i < 3; i++)
  {
    printf("thread 2: data_for_thread[%d] = %f\n", i, ((double*)arg)[i]);
    ((double*)arg)[i] += 2.0;
  }
  return NULL;
}

int main() {
  printf("This is the main() function starting.\n");

  double data_for_thread[3];
  data_for_thread[0] = 5.7;
  data_for_thread[1] = 9.2;
  data_for_thread[2] = 1.6;

  /* Start thread. */
  pthread_t thread;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread, NULL, the_thread_func, data_for_thread);

  pthread_t thread2;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread2, NULL, the_thread_func2, data_for_thread);


  printf("This is the main() function after pthread_create()\n");

  /* Do something here? */
  printf("main() starting doing some work.\n");
  for(int i = 0; i < 3; i++)
  {
    printf("main: data_for_thread[%d] = %f\n", i, ((double*)data_for_thread)[i]);
  }

  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  pthread_join(thread, NULL);
  pthread_join(thread2, NULL);

  return 0;
}
