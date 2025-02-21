#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    double d;
    char c;
    float f;
    FILE *file = fopen("little_bin_file", "r");
    if (file == NULL) {
        printf("Error: File not found\n");
        exit(1);
    }
    fread(&n, sizeof(int), 1, file);
    fread(&d, sizeof(double), 1, file);
    fread(&c, sizeof(char), 1, file);
    fread(&f, sizeof(float), 1, file);
    printf("%d\n", n);
    printf("%f\n", d);
    printf("%c\n", c);
    printf("%f\n", f);
    fclose(file);
    return 0;
}