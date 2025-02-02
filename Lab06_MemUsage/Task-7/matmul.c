#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
 
static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}
int rand_int(int N)
{
  int val = -1;
  while( val < 0 || val >= N )
    {
      val = (int)(N * (double)rand()/RAND_MAX);
    }
  return val;
}

void allocate_mem(int*** arr, int n)
{
  int i;
  *arr = (int**)malloc(n*sizeof(int*));
  for(i=0; i<n; i++)
    (*arr)[i] = (int*)malloc(n*sizeof(int));
}

void free_mem(int** arr, int n)
{
  int i;
  for(i=0; i<n; i++)
    free(arr[i]);
  free(arr);
}

/* kij */
void mul_kij(int n, int **a, int **b, int **c)
{
  int i, j, k;
  for (k=0; k<n; k++) {
    for (i=0; i<n; i++) {
      int x = a[i][k];
      for (j=0; j<n; j++)
        c[i][j] += x * b[k][j];   
      }
  }
}

void mul_kij_blocking(int n, int **a, int **b, int **c)
{
  const int blockSz = 10;
  int subMat[blockSz*blockSz];
  if(n % blockSz != 0) {
    printf("Error: N not divisible by blockSz.\n");
    return;
  }
  int nBlocks = n / blockSz;
  int block_i, block_j, block_k;
  int i, j, k;
  for (block_i = 0; block_i < nBlocks; block_i++) {
    int iStart = block_i * blockSz;
    for (block_j = 0; block_j < nBlocks; block_j++) {
      int jStart = block_j * blockSz;
      for (block_k = 0; block_k < nBlocks; block_k++) {
        int kStart = block_k * blockSz;
        for (k = 0; k < blockSz; k++) {
          for (i = 0; i < blockSz; i++) {
            int x = a[iStart + i][kStart + k];
            for (j = 0; j < blockSz; j++) {
              subMat[j*blockSz+i] += x * b[kStart + k][jStart + j];
            }
          }
          for (i = 0; i < blockSz; i++) {
            for (j = 0; j < blockSz; j++) {
              c[iStart + i][jStart + j] += subMat[j*blockSz+i];
            }
          }
        }
      }
    }
  }
}

/* ijk */
void mul_ijk(int n, int **a, int **b, int **c)
{
  int i, j, k;
  for (i=0; i<n; i++)  {
    for (j=0; j<n; j++) {
      int sum = 0;
      for (k=0; k<n; k++) 
	sum += a[i][k] * b[k][j];
      c[i][j] = sum;
    }
  }
}

/* jik */
void mul_jik(int n, int **a, int **b, int **c)
{
  int i, j, k;
  for (j=0; j<n; j++) {
    for (i=0; i<n; i++) {
      int sum = 0;
      for (k=0; k<n; k++)
	sum += a[i][k] * b[k][j];
      c[i][j] = sum;
    }
  }
}

int main()
{
  int i, j, n;
  int **a;
  int **b;
  int **c;
  double time;
  int Nmax = 100; // random numbers in [0, N]

  printf("Enter the dimension of matrices n = ");
  if(scanf("%d", &n) != 1) {
    printf("Error in scanf.\n");
    return -1;
  }

  allocate_mem(&a, n);

  for ( i = 0 ; i < n ; i++ )
    for ( j = 0 ; j < n ; j++ )
      a[i][j] = rand_int(Nmax);

  allocate_mem(&b, n);
 
  for ( i = 0 ; i < n ; i++ )
    for ( j = 0 ; j < n ; j++ )
      b[i][j] = rand_int(Nmax);

  allocate_mem(&c, n);

  time=get_wall_seconds();
  mul_kij(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version kij, time = %f\n",time);
  time=get_wall_seconds();
  mul_ijk(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version ijk, time = %f\n",time);
  time=get_wall_seconds();
  mul_jik(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version jik, time = %f\n",time);
  time=get_wall_seconds();
  mul_kij_blocking(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version kij, time = %f\n",time);

  /*
    printf("Product of entered matrices:\n");
 
    for ( i = 0 ; i < n ; i++ )
    {
    for ( j = 0 ; j < n ; j++ )
    printf("%d\t", c[i][j]);
 
    printf("\n");
    }
  */

  free_mem(a, n);
  free_mem(b, n);
  free_mem(c, n);

  return 0;
}
