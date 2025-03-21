/**
 * version: bitmask parallel with better runtime than bitmask_parallel_same.c
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <omp.h>

uint8_t base;
uint8_t side_length;
int n_thread;
bool is_solved = false;
uint8_t *solved_board;
void print_sudoku(uint8_t *board, uint8_t side_length)
{
    printf("Sudoku Board:\n");
    for (int i = 0; i < side_length; i++)
    {
        for (int j = 0; j < side_length; j++)
        {
            printf("%3u ", board[i * side_length + j]);
        }
        printf("\n");
    }
}

bool duplicate_number_in_row(uint8_t *board, uint8_t x)
{
    uint8_t *row = board + x * side_length;
    for (int i = 0; i < side_length; i++)
    {
        if (row[i] == 0)
            continue;
        for (int j = i + 1; j < side_length; j++)
        {
            if (row[j] == 0)
                continue;
            if (row[i] == row[j])
                return true;
        }
    }
    return false;
}

bool duplicate_number_in_column(uint8_t *board, uint8_t y)
{
    for (int i = 0; i < side_length; i++)
    {
        if (board[i * side_length + y] == 0)
            continue;
        for (int j = i + 1; j < side_length; j++)
        {
            if (board[j * side_length + y] == 0)
                continue;
            if (board[i * side_length + y] == board[j * side_length + y])
                return true;
        }
    }
    return false;
}

bool duplicate_number_in_box(uint8_t *board, uint8_t x, uint8_t y)
{
    uint8_t box_x = x / base;
    uint8_t box_y = y / base;
    uint8_t start_x = box_x * base;
    uint8_t start_y = box_y * base;
    uint8_t end_x = start_x + base;
    uint8_t end_y = start_y + base;
    for (int i = start_x; i < end_x; ++i)
    {
        for (int j = start_y; j < end_y; ++j)
        {
            if (board[i * side_length + j] == 0)
                continue;
            for (int k = i; k < end_x; ++k)
            {
                for (int l = j; l < end_y; ++l)
                {
                    if (board[k * side_length + l] == 0)
                        continue;
                    if (board[i * side_length + j] == board[k * side_length + l] && i != k && j != l)
                        return true;
                }
            }
        }
    }
    return false;
}


bool validate_board(uint8_t *board, uint8_t x, uint8_t y)
{
    // if (duplicate_number_in_row(board, x))
    //     return false;
    // if (duplicate_number_in_column(board, y))
    //     return false;
    // if (duplicate_number_in_box(board, x, y))
    //     return false;
    // return true;
    // check row
    for (int i = 0; i < side_length; i++)
    {
        if (board[x * side_length + i] == board[x * side_length + y] && i != y)
            return false;
    }
    // check column
    for (int i = 0; i < side_length; i++)
    {
        if (board[i * side_length + y] == board[x * side_length + y] && i != x)
            return false;
    }
    // check box
    uint8_t box_x = x / base;
    uint8_t box_y = y / base;
    uint8_t start_x = box_x * base;
    uint8_t start_y = box_y * base;
    uint8_t end_x = start_x + base;
    uint8_t end_y = start_y + base;
    for (int i = start_x; i < end_x; ++i)
    {
        for (int j = start_y; j < end_y; ++j)
        {
            if (board[i * side_length + j] == board[x * side_length + y] && i != x && j != y)
                return false;
        }
    }
    return true;
}



bool solve(uint8_t *board, int *unassign_ind, int n_unassign)
{
    // no more empty position, solution found
    if (n_unassign == 0)
    {
        #pragma omp critical
        {
            is_solved = true;
            for (int i = 0; i < side_length * side_length; i++)
            {
                solved_board[i] = board[i];
            }
        }
        return true;
    }
    if (is_solved)
        return false;

    uint8_t x = unassign_ind[n_unassign - 1] / side_length;
    uint8_t y = unassign_ind[n_unassign - 1] % side_length;
    // printf("Solving cell (%u, %u)\n", x, y);

    
    for (int val = 1; val <= side_length; ++val)
    {
        // set guess
        board[x * side_length + y] = val;
        // printf("Guessing %u\n", val);
        if (validate_board(board, x, y))
        {
            bool solved = solve(board, unassign_ind, n_unassign - 1);
            if (solved)
            {
                #pragma omp critical
                {
                    is_solved = true;
                }
                return true;
            }
        }
    }
    // no solution found, backtrack
    board[x * side_length + y] = 0;
    return false;
}


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: sudoku <file> <n_thread>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        printf("Could not open file %s.\n", argv[1]);
        return 1;
    }

    n_thread = atoi(argv[2]);
    
    // read base 和 side_length
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

    
    solved_board = (uint8_t*)malloc(side_length * side_length * sizeof(uint8_t)); 
    if (solved_board == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1;
    }
    if(fread(solved_board, sizeof(uint8_t), side_length * side_length, file) != side_length * side_length)
    {
        printf("Failed to read board.\n");
        fclose(file);
        return 1;
    }

    fclose(file);

    printf("initial sudoku board:\n");
    print_sudoku(solved_board, side_length);

    // find unassigned cells
    int n_unassign = 0;
    // unassign_ind is a 1D array to store the index of unassigned cells
    // side_length * side_length is the maximum number of unassigned cells
    int *unassign_ind = (int *)malloc(side_length * side_length * sizeof(int));
    for (int i = 0; i < side_length; ++i)
    {
        for (int j = 0; j < side_length; ++j)
        {
            if (solved_board[i * side_length + j] == 0)
            {
                unassign_ind[n_unassign] = i * side_length + j;
                n_unassign++;
            }
        }
    }

    // printf("Number of unassigned cells: %u\n", n_unassign);
    // printf("Unassigned cells:\n");
    // for (int i = 0; i < n_unassign; ++i)
    // {
    //     printf("(%u, %u)\n", unassign_ind[i] / side_length, unassign_ind[i] % side_length);
    // }

    // solve sudoku
    // only parallel first level
    #pragma omp parallel num_threads(n_thread)
    {
        #pragma omp single nowait
        {
            for (int val = 1; val <= side_length; ++val)
            {
                if (is_solved)
                    continue;
                int x = unassign_ind[n_unassign - 1] / side_length;
                int y = unassign_ind[n_unassign - 1] % side_length;

                uint8_t board_copy[side_length * side_length]; 
                for (int i = 0; i < side_length * side_length; i++)
                {
                    board_copy[i] = solved_board[i];
                }
                // set guess
                board_copy[x * side_length + y] = val;
                #pragma omp task firstprivate(board_copy) shared(is_solved)
                {
                    if (validate_board(board_copy, x, y))
                    {
                        bool solved = solve(board_copy, unassign_ind, n_unassign - 1);
                        if (solved)
                        {
                            #pragma omp critical
                            {
                                is_solved = true;
                            }
                        }
                    }
                }
            }
        }
    }
    


    printf("solution:\n");
    print_sudoku(solved_board, side_length);

    free(solved_board);
    return 0;
}