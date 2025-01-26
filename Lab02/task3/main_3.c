#include <stdio.h>
#include <math.h>

double _abs(double x)
{
    if (x < 0)
    {
        return -x;
    }
    return x;
}

int main()
{
    double a, b, c;
    scanf("%lf %lf %lf", &a, &b, &c);
    a = _abs(a);
    b = _abs(b);
    c = _abs(c);
    // find the second largest number
    if ((a > b && a < c) || (a < b && a > c))
    {
        printf("%lf\n", a);
    }
    else if ((b > a && b < c) || (b < a && b > c))
    {
        printf("%lf\n", b);
    }
    else
    {
        printf("%lf\n", c);
    }

    return 0;
}