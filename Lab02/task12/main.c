#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isPrime(int n)
{
    if (n < 2)
    {
        return false;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int n;
    scanf("%d", &n);
    int* arr;
    arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int* notprime;
    notprime = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        if (!isPrime(arr[i]))
        {
            notprime[i] = arr[i];
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (notprime[i] != 0)
        {
            printf("%d ", notprime[i]);
        }
    }
    printf("\n");
    free(arr);
    free(notprime);
    return 0;
}