#include <stdio.h>
#include <math.h>

int main()
{
    double a;
    scanf("%lf", &a);
    if (sqrt(a) == (int)sqrt(a))
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
    return 0;

}