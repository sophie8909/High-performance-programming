#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct product
{
    char name[50];
    double price;
}
product_t;

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
    product_t *arr_of_prod = (product_t *)malloc(n * sizeof(product_t));
    for (int i = 0; i < n; i++) {
        product_t p;
        fscanf(file, "%s %lf", p.name, &p.price);
        arr_of_prod[i] = p;
    }
    for (int i = 0; i < n; i++) {
        printf("%s %.2lf\n", arr_of_prod[i].name, arr_of_prod[i].price);
    }

    free(filename);
    free(arr_of_prod);
    fclose(file);
    
    return 0;
}