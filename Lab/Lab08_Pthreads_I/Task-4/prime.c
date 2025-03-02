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
    
    double time = get_wall_seconds();

    /* Start thread. */
    pthread_t thread;
    ThreadData data = {M/4, M, 0};

    printf("the main() function now calling pthread_create().\n");
    pthread_create(&thread, NULL, count_primes_thread, &data);

    printf("This is the main() function after pthread_create()\n");

    int count = 0;
    for (int i = 1; i < M/4; ++i) {
        if (is_prime(i)) {
            count++;
        }
    }

    time = get_wall_seconds() - time;

    printf("Number of primes: %d\n", count);
    printf("Number of primes computed by thread: %d\n", data.count);
    printf("Total number of primes: %d\n", count + data.count);

    /* Wait for thread to finish. */
    printf("the main() function now calling pthread_join().\n");
    pthread_join(thread, NULL);
    
    printf("Time taken: %f\n", time);

}