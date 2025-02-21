#include <stdio.h>
#include <stdlib.h>

void print_int_1(int x) {
    printf("Here is the number: %d\n", x);
}
void print_int_2(int x) {
    printf("Wow, %d is really an impressive number!\n", x);
}



int main()
{
    void (*print_int)(int);
    int x = 5;
    print_int = print_int_1;
    print_int(x);
    print_int = print_int_2;
    print_int(x);
    return 0;
}