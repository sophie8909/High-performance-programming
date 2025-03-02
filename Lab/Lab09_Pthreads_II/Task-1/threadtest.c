#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* the_thread_func(void* arg) {
  /* Do something here? */
  int* p = (int*)malloc(10 * sizeof(int));
  for (int i = 0; i < 10; i++) {
    p[i] = i;
  }
  return p;
}

int main() {
  printf("This is the main() function starting.\n");

  /* Start thread. */
  pthread_t thread;
  printf("the main() function now calling pthread_create().\n");
  if(pthread_create(&thread, NULL, the_thread_func, NULL) != 0) {
    printf("ERROR: pthread_create failed.\n");
    return -1;
  }

  printf("This is the main() function after pthread_create()\n");

  /* Do something here? */
  int* p = NULL;
  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  if(pthread_join(thread, (void*)&p) != 0) {
    printf("ERROR: pthread_join failed.\n");
    return -1;
  }

  for (int i = 0; i < 10; i++) {
    printf("%d\n", p[i]);
  }

  free(p);

  return 0;
}
