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
    int parent_thread;
} ThreadData;
void *print_thread_2(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    printf("Hello from thread %d\n", data->index_thread);
    printf("parent thread: %d\n", data->parent_thread);
    
    return NULL;
}

void *print_thread_1(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    printf("Hello from thread %d\n", data->index_thread);
    printf("parent thread: %d\n", data->parent_thread);
    pthread_t thread1;
    ThreadData data1;
    data1.index_thread = data->index_thread*2+1;
    data1.parent_thread = data->index_thread;

    pthread_t thread2;
    ThreadData data2;
    data2.index_thread = data->index_thread*2 + 2;
    data2.parent_thread = data->index_thread;
    pthread_create(&thread1, NULL, print_thread_2, &data1);
    pthread_create(&thread2, NULL, print_thread_2, &data2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return NULL;
}

int main() {
    printf("This is the main() function starting.\n");

    
    double time = get_wall_seconds();

    /* Start thread. */
    pthread_t thread1;
    ThreadData data1;
    data1.index_thread = 1;
    data1.parent_thread = 0;

    pthread_t thread2;
    ThreadData data2;
    data2.index_thread = 2;
    data2.parent_thread = 0;

    pthread_create(&thread1, NULL, print_thread_1, &data1);
    pthread_create(&thread2, NULL, print_thread_1, &data2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("This is the main() function ending.\n");
    printf("Time elapsed: %.6f seconds.\n", get_wall_seconds() - time);
    return 0;
}

