#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    if (a % 2 == 0 && b % 2 == 0)
    {
        printf("%d\n", a+b);
    }
    else
    {
        printf("%d\n", a*b);
    }
    return 0;
}