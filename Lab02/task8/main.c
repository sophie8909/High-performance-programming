#include <stdio.h>

int main()
{
    double a;
    int b;
    char c;
    scanf("%lf %d %c", &a, &b, &c);
    // Output the value of each input variable, its address, and its memory size (in bytes)
    printf("a = %lf, address = %p, size = %lu\n", a, &a, sizeof(a));
    printf("b = %d, address = %p, size = %lu\n", b, &b, sizeof(b));
    printf("c = %c, address = %p, size = %lu\n", c, &c, sizeof(c));
    return 0;
}