#include <stdio.h> 

int main()
{
    int i = 100;
    while (i >= 0)
    {
        printf("%d\n", i);
        i -= 4;
    }
    return 0;
}