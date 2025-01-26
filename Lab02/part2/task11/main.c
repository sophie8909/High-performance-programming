#include <stdio.h>
#include <stdlib.h>

int main()
{
    int* arr;
    int n = 5;
    arr = (int*)malloc(n * sizeof(int));
    int x;
    int i = 0;
    int sum = 0;
    printf("Input: ");
    // input until input not integer
    while(scanf("%d", &x) == 1)
    {
        if(i == n)
        {
            n *= 2;
            arr = (int*)realloc(arr, n * sizeof(int));
        }
        arr[i] = x;
        sum += x;
        ++i;
    }
    // output
    printf("Output: ");
    for(int j = 0; j < i; ++j)
    {
        printf("%d ", arr[j]);
    }
    printf("\nSum: %d\n", sum);
    return 0;
}