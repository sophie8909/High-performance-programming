#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    
    // Open file
    char *filename;
    if (argc > 1)
        filename = (char *)malloc(sizeof(filename) * sizeof(char)); 
        strcpy(filename, argv[1]);
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File not found\n");
        return 1;
    }
    int n;
    fscanf(file, "%d", &n);
    char *product = (char *)malloc(50 * sizeof(char));
    double price;
    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %lf", product, &price);
        printf("%s %.2lf\n", product, price);
    }
    return 0;
}