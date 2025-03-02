/**********************************************************************
 * Enumeration sort
 *
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define NUM_THREADS	8
#define len 100000

typedef struct {
  int id;  // Thread ID
  int start;  // Start index
  int end;  // End index
} ThreadData;

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

double indata[len], outdata[len];

void *findrank(void *arg)
{
  ThreadData* data = (ThreadData*) arg;

	for (int i=data->start;i<data->end;++i)
  {
    int rank=0;
    for (int j=0;j<len;++j)
    {
      if (indata[i]>indata[j]) rank++;
    }
    outdata[rank]=indata[i];
  }
	pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
	
  pthread_t threads[NUM_THREADS];
  pthread_attr_t attr;
  int i, t;
  void *status;
  
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);	

  // Generate random numbers
  for (i=0;i<len;i++){
      indata[i]=drand48();
      outdata[i]=-1.0;
  }

  // Enumeration sort
  double startTime = get_wall_seconds();

  ThreadData data[NUM_THREADS];
  // Create threads
  for (t=0; t<NUM_THREADS; t++) {
    data[t].id = t;
    data[t].start = t*len/NUM_THREADS;
    data[t].end = (t+1)*len/NUM_THREADS;
    pthread_create(&threads[t], &attr, findrank, (void*)&data[t]);
  }

  // Wait for threads to finish
  for (t=0; t<NUM_THREADS; t++)
    pthread_join(threads[t], &status);


  double timeTaken = get_wall_seconds() - startTime;
  printf("Time: %f  NUM_THREADS: %d\n", timeTaken, NUM_THREADS);

  // Check results, -1 implies data same as the previous element
    for (i=0; i<len-1; i++)
      if (outdata[i]>outdata[i+1] && outdata[i+1]>-1)
	printf("ERROR: %f,%f\n", outdata[i],outdata[i+1]);

  return 0;
}
