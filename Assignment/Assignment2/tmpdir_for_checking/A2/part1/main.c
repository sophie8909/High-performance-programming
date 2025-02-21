#include <stdio.h>  
#include <stdlib.h>




int main(int argc, char* argv[])
{
    // if argv[0] is exist
    if (argc > 0)
    {
        int n = atoi(argv[1]);
        int* row = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; ++i)
        {
            row[i] = 1;
            for (int j = i-1; j > 0; --j)
            {
                row[j] = row[j] + row[j - 1];
            }
            for (int j = 0; j <= i; ++j)
            {
                printf("%d ", row[j]);
            }
            printf("\n");
        }
    }
    else
    {
        // print the error message
        printf("No arguments were given\n");
    }
}