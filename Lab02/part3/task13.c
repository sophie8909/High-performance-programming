#include <stdio.h>
#include <stdlib.h>

int main() {
    
    // Open file
    FILE *file = fopen("data.txt", "r");
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