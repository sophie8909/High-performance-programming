#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <math.h>
 
static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}
typedef struct {
    int start;
    int end;
    int count;
    int index_thread;
} ThreadData;

// Function to check if a number is prime
int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

// Function executed by each thread
void *count_primes_thread(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int count = 0;

    for (int i = data->start; i <= data->end; i++) {
        if (is_prime(i)) {
            count++;
        }
    }

    data->count = count;
    return NULL;
}

int main() {
    printf("This is the main() function starting.\n");


    printf("Input M: ");
    int M;
    scanf("%d", &M);
    printf("Input N: ");
    int N;
    scanf("%d", &N);

    double time = get_wall_seconds();

    /* Start thread. */
    pthread_t thread[N];
    ThreadData data[N];
    for (int i = 0; i < N; i++) {
        data[i].index_thread = i;
        data[i].start = i * M / N + 1;
        data[i].end = (i + 1) * M / N;
        printf("the main() function now calling pthread_create().\n");
        pthread_create(&thread[i], NULL, count_primes_thread, &data[i]);
    }
    int count = 0;
    for (int i = 0; i < N; i++) {
        pthread_join(thread[i], NULL);
        count += data[i].count;
    }


    printf("Number of primes: %d\n", count);

    /* Wait for thread to finish. */
    printf("This is the main() function ending.\n");
    printf("Time elapsed: %.6f seconds.\n", get_wall_seconds() - time);
    
    printf("Time taken: %f\n", time);

}