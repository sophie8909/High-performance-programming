#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

typedef struct {
    int index_thread;
} ThreadData;


void *print_thread(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    printf("Hello from thread %d\n", data->index_thread);
    return NULL;
}

int main() {
    printf("This is the main() function starting.\n");

    printf("Input N: ");
    int N;
    scanf("%d", &N);
    
    double time = get_wall_seconds();

    /* Start thread. */
    pthread_t thread[N];
    ThreadData data[N];
    for (int i = 0; i < N; i++) {
        data[i].index_thread = i;
        printf("the main() function now calling pthread_create().\n");
        pthread_create(&thread[i], NULL, print_thread, &data[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(thread[i], NULL);
    }

    printf("This is the main() function ending.\n");
    printf("Time elapsed: %.6f seconds.\n", get_wall_seconds() - time);
    return 0;
}

