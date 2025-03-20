#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "sort_funcs.h"

void bubble_sort(intType* list, int N) {
    int i, j;
    for (i = 0; i < N - 1; i++)
        for (j = i + 1; j < N; j++) {
            if (list[i] > list[j]) {
                // Swap
                intType tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
        }
}


void merge_sort(intType* list_to_sort, int N, int nThreads) {
  if(N == 1) {
    // Only one element, no sorting needed. Just return directly in this case.
    return;
  }
  int n1 = N / 2;
  int n2 = N - n1;
  // Allocate new lists
  intType* list1 = (intType*)malloc(N*sizeof(intType));
  intType* list2 = list1 + n1;
  int i;
  for(i = 0; i < n1; i++)
    list1[i] = list_to_sort[i];
  for(i = 0; i < n2; i++)
    list2[i] = list_to_sort[n1+i];
  // Sort list1 and list2
  if (nThreads > 1) {
    // 使用 OpenMP 並行遞迴
    #pragma omp parallel 
    {
        #pragma omp single
        {
            #pragma omp task
            merge_sort(list1, n1, nThreads / 2);
            #pragma omp task
            merge_sort(list2, n2, nThreads / 2);
        }
      #pragma omp taskwait
    }
  } else {
      // 單執行緒時，直接遞迴呼叫
      merge_sort(list1, n1, 1);
      merge_sort(list2, n2, 1);
  }
  // Merge!
  int i1 = 0;
  int i2 = 0;
  i = 0;
  while(i1 < n1 && i2 < n2) {
    if(list1[i1] < list2[i2]) {
      list_to_sort[i] = list1[i1];
      i1++;
    }
    else {
      list_to_sort[i] = list2[i2];
      i2++;
    }
    i++;
  }
  while(i1 < n1)
    list_to_sort[i++] = list1[i1++];
  while(i2 < n2)
    list_to_sort[i++] = list2[i2++];
  free(list1);
}

void *merge_sort_thread(void *data) {
  // printf("merge_sort\n");
    ThreadData* threadData = (ThreadData*)data;
    int N = threadData->N;
    intType* list_to_sort = threadData->list;
    int nThreads = threadData->nThreads;

    // Base case: Stop if the array has 1 or fewer elements
    if (N <= 1) {
        pthread_exit(NULL);
    }

    int n1 = N / 2;
    int n2 = N - n1;

    // Allocate separate memory for list1 and list2
    intType* list1 = (intType*)malloc(n1 * sizeof(intType));
    intType* list2 = (intType*)malloc(n2 * sizeof(intType));

    if (!list1 || !list2) {
        perror("Memory allocation failed");
        free(list1);
        free(list2);
        return NULL;
    }

    // Copy elements into the new arrays
    for (int i = 0; i < n1; i++)
        list1[i] = list_to_sort[i];
    for (int i = 0; i < n2; i++)
        list2[i] = list_to_sort[n1 + i];

    // Create thread data for recursive calls
    ThreadData data1 = {n1, list1, nThreads / 2};
    ThreadData data2 = {n2, list2, nThreads - nThreads / 2};

    int useThreads = (nThreads > 1);
    
    if (useThreads) {
      // printf("left thread %d\n", nThreads / 2);
      // Initialize thread attributes
      pthread_t thread1;
      pthread_t thread2;
      pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        // Create a new thread for sorting the first half
        pthread_create(&thread1, &attr, merge_sort_thread, (void*)&data1);
        pthread_create(&thread2, &attr, merge_sort_thread, (void*)&data2);


        // Wait for the first half to finish
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        // printf("pthread join\n");
        pthread_attr_destroy(&attr);
    } else {
        // printf("no thread\n");
        // Sequential recursive sorting
        merge_sort(list1, n1, 1);
        merge_sort(list2, n2, 1);
        // printf("no thread end\n");
    }

    // Merge sorted halves back into the original array
    int i = 0, i1 = 0, i2 = 0;
    while (i1 < n1 && i2 < n2) {
        if (list1[i1] < list2[i2])
            list_to_sort[i++] = list1[i1++];
        else
            list_to_sort[i++] = list2[i2++];
    }
    while (i1 < n1)
        list_to_sort[i++] = list1[i1++];
    while (i2 < n2)
        list_to_sort[i++] = list2[i2++];

    // for (int i = 0; i < N; i++)
    //     printf("%d ", list_to_sort[i]);
    // printf("\n");

    // Free allocated memory
    free(list1);
    free(list2);

    return NULL;
}
