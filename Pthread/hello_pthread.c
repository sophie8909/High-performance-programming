#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *hello(void *arg) {
    printf("Hello from thread %d\n", *(int*)arg);
    return NULL;
}

int main(int argc, char* argv[]) {

    pthread_t thread[4];

    for(int i = 0; i < 4; i++) {
        pthread_create(&thread[i], NULL, hello, (void*)&i);
    }
    
    for(int i = 0; i < 4; i++) {
        pthread_join(thread[i], NULL);
    }


    return 0;
}