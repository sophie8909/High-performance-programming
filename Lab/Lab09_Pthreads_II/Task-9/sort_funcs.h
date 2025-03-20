typedef int intType;

void bubble_sort(intType* list, int N);
void *merge_sort_thread(void *data);

typedef struct {
    int N;
    intType* list;
    int nThreads;
  } ThreadData;
  