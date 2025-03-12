#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: sudoku <file>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        printf("Could not open file %s.\n", argv[1]);
        return 1;
    }

    // read base 和 side_length
    uint8_t base, side_length;
    if (fread(&base, sizeof(uint8_t), 1, file) != 1)
    {
        printf("Failed to read base.\n");
        fclose(file);
        return 1;
    }
    if (fread(&side_length, sizeof(uint8_t), 1, file) != 1)
    {
        printf("Failed to read side length.\n");
        fclose(file);
        return 1;
    }

    printf("Base: %u, Side length: %u\n", base, side_length);

    
    uint8_t **data = (uint8_t **)malloc(side_length * sizeof(uint8_t *));
    for (int i = 0; i < side_length; ++i)
    {
        data[i] = (uint8_t *)malloc(side_length * sizeof(uint8_t));
    }
    if (data == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1;
    }
    for (int i = 0; i < side_length; ++i)
    {
        for (int j = 0; j < side_length; ++j)
        {
            fread(&data[i][j], sizeof(uint8_t), 1, file);
        }
    }

    fclose(file);

    // print the sudoku board
    printf("Sudoku Board:\n");
    for (int i = 0; i < side_length; i++)
    {
        for (int j = 0; j < side_length; j++)
        {
            printf("%3u ", data[i][j]);
        }
        printf("\n");
    }

    free(data);
    return 0;
}
