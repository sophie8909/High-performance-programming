#include <stdio.h>

int main()
{
    int a;
    printf("Input: ");
    scanf("%d", &a);
    int temp = a;
    int rev_a = 0;
    while (temp > 0)
    {
        rev_a = rev_a * 10 + temp % 10;
        temp /= 10;
    }
    if (a == rev_a)
    {
        printf(" it is a palindrome\n");
    }
    else
    {
        printf("it is not a palindrome\n");
    }
}