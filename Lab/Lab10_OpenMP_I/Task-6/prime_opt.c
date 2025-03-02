#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>


int M = 0;
int N = 4;

typedef struct {
    int id;
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
void count_primes_thread(ThreadData *data) {
    int count = 0;
    int batch = 100;
    
    for (int i = data->id * batch; i <= M; i+=N*batch) {
        // min(i + batch, M)
        int end = i + batch;
        if (end > M) {
            end = M;
        }
        for (int j = i; j < end; ++j)
        {
            if (is_prime(j)) {
                count++;
            }
        }
    }

    data->count = count;
    return;
}

int main(int argc, char *argv[]) {
    M = atoi(argv[1]);
    N = atoi(argv[2]);
    
    double start_time = omp_get_wtime();
    ThreadData data[N];
    int count = 0;
#pragma omp parallel num_threads(N)
    {
        int id = omp_get_thread_num();
        data[id].id = id;
        data[id].start = id * M / N + 1;
        data[id].end = (id + 1) * M / N;
        data[id].count = 0;
        count_primes_thread(&data[id]);
    }

    for (int i = 0; i < N; i++) {
        count += data[i].count;
    }

    double end_time = omp_get_wtime();
    printf("Number of primes: %d\n", count);

    printf("Time taken: %f\n", end_time - start_time);

}