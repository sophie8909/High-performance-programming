#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int A[N][N];

typedef struct {
    int start;
    int end;
    int k;
    int n;
} ThreadData;

void *LU_part1(void *arg) {

    ThreadData data = *(ThreadData*)arg;
    int start = data.start;
    int end = data.end;
    int k = data.k;
    int n = data.n;
    for (int i = start; i < end; ++i)
    {
        A[i][k] = A[i][k] / A[k][k];
    }
    for (int i = start; i < end; ++i)
    {
        for (j = k+1; j < n; ++j)
            A[i][j] = A[i]j[j] - A[i][k]*A[k][j];
    }

    return NULL;
}

void *LU_part2(void *arg) {

    ThreadData data = *(ThreadData*)arg;
    int start = data.start;
    int end = data.end;
    

    return NULL;
}


int main(int argc, char* argv[]) {

    pthread_t thread[4];

    for (int k = 0; k < n; ++k)
    {
        ThreadData data[4];
        batch_size = (n-k) / 4;
        

        for(int i = 0; i < 4; i++) {
            data[i].start = k + i * batch_size;
            data[i].end = data[i].start + batch_size;
            pthread_create(&thread[i], NULL, LU, (void*)&i);
        }
        for(int i = 0; i < 4; i++) {
            pthread_join(thread[i], NULL);
        }
    }



    
    
    


    return 0;
}