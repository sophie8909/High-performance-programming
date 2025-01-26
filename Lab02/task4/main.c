#include <stdio.h>

int main()
{
    double a, b;
    char op;
    scanf("%lf %c %lf", &a, &op, &b);
    switch (op)
    {
    case '+':
        printf("%lf\n", a + b);
        break;
    case '-':

        printf("%lf\n", a - b);
        break;
    case '*':
        printf("%lf\n", a * b);
        break;
    case '/':   
        if (b == 0)
        {
            printf("Division by zero!\n");
        }
        else
        {
            printf("%lf\n", a / b);
        }
        break;
    default:
        printf("Invalid operator!\n");
        break;
    }
    return 0;
}