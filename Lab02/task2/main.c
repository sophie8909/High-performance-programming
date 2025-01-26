#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    for (int i = 0; i < b; i++)
    {
        printf("*");
    }
    printf("\n");
    for (int i = 0; i < a - 2; i++)
    {
        printf("*");
        for (int j = 0; j < b - 2; j++)
        {
            printf(".");
        }
        printf("*\n");
    }
    for (int i = 0; i < b; i++)
    {
        printf("*");
    }
    printf("\n");
    return 0;
}