#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <omp.h>
#include <string.h>

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

bool validate_board_bitmask(uint8_t* board, uint64_t* board_row, uint64_t* board_col, uint64_t* board_box, uint8_t x, uint8_t y, uint8_t val)
{
    // printf("Validating cell (%u, %u) with value %u\n", x, y, val);
    uint64_t mask = 1ULL << (uint64_t)(val-1);
    if ((board_row[x] & mask) != 0)
        return false;
    if ((board_col[y] & mask) != 0)
        return false;
    if ((board_box[(x / base) * base + y / base] & mask) != 0)
        return false;

    // printf("Cell (%u, %u) with value %u is valid\n", x, y, val);
    return true;
}

void solve(uint8_t *board, uint64_t* board_row, uint64_t* board_col, uint64_t* board_box, int *unassign_ind, int n_unassign)
{
    if (is_solved)
        return;
    // no more empty position, solution found
    if (n_unassign == 0)
    {
        // printf("solution found in thread %d\n", omp_get_thread_num());]
        #pragma omp critical
        {
            is_solved = true;
            for (int i = 0; i < side_length * side_length; i++)
            {
                solved_board[i] = board[i];
            }
        }
        return;
    }

    uint8_t x = unassign_ind[n_unassign - 1] / side_length;
    uint8_t y = unassign_ind[n_unassign - 1] % side_length;
    // printf("Solving cell (%u, %u)\n", x, y);

    
    for (int val = 1; val <= side_length; ++val)
    {
        if (is_solved)
            continue;
        // set guess
        board[x * side_length + y] = val;
        // printf("Guessing %u\n", val);
        bool should_create_task = false;
        if (omp_get_num_threads() < n_thread)
        {
            should_create_task = true;
        }
        if (should_create_task)
        {
            #pragma omp task firstprivate(board, board_row, board_col, board_box, unassign_ind, n_unassign, x, y) shared(is_solved)
            {
                uint8_t board_copy[side_length * side_length];
                uint64_t board_row_copy[side_length];
                uint64_t board_col_copy[side_length];
                uint64_t board_box_copy[side_length];
                memcpy(board_copy, board, side_length * side_length * sizeof(uint8_t));
                memcpy(board_row_copy, board_row, side_length * sizeof(uint64_t));
                memcpy(board_col_copy, board_col, side_length * sizeof(uint64_t));
                memcpy(board_box_copy, board_box, side_length * sizeof(uint64_t));
    
                if (validate_board_bitmask(board_copy, board_row_copy, board_col_copy, board_box_copy, x, y, val))
                {
                    uint64_t mask = 1ULL << (uint64_t)(val-1);
                    // update bitmask
                    board_row_copy[x] |= mask;
                    board_col_copy[y] |= mask;
                    board_box_copy[(x / base) * base + y / base] |= mask;
                    // solve next cell
                    // printf("Solving cell (%u, %u)\n", x, y);
                    solve(board_copy, board_row_copy, board_col_copy, board_box_copy, unassign_ind, n_unassign - 1);
                    board_row_copy[x] &= ~mask;
                    board_col_copy[y] &= ~mask;
                    board_box_copy[(x / base) * base + y / base] &= ~mask;
                }
            }
        }
        else
        {
            if (validate_board(board, x, y))
            {
                uint64_t mask = 1ULL << (uint64_t)(val-1);
                // update bitmask
                board_row[x] |= mask;
                board_col[y] |= mask;
                board_box[(x / base) * base + y / base] |= mask;
                solve(board, board_row, board_col, board_box, unassign_ind, n_unassign - 1);
                board_row[x] &= ~mask;
                board_col[y] &= ~mask;
                board_box[(x / base) * base + y / base] &= ~mask;
            }
        }
    }
    
    // no solution found, backtrack
    board[x * side_length + y] = 0;
    return;
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

    /* set init bit map */
    // row
    uint64_t board_row[side_length];
    memset(board_row, 0, side_length * sizeof(uint64_t));

    for (int i = 0; i < side_length; ++i)
    {
        for (int j = 0; j < side_length; ++j)
        {
            if (solved_board[i * side_length + j] != 0)
            {
                board_row[i] |= 1ULL << (solved_board[i * side_length + j] - 1);
            }
        }
    }

    // column
    uint64_t board_col[side_length];
    memset(board_col, 0, side_length * sizeof(uint64_t));
    for (int i = 0; i < side_length; ++i)
    {
        for (int j = 0; j < side_length; ++j)
        {
            if (solved_board[j * side_length + i] != 0)
            {
                board_col[i] |= 1ULL << (solved_board[j * side_length + i] - 1);
            }
        }
    }

    // box
    uint64_t board_box[side_length];
    memset(board_box, 0, side_length * sizeof(uint64_t));
    for (int base_x = 0; base_x < base; ++base_x)
    {
        for (int base_y = 0; base_y < base; ++base_y)
        {
            for (int i = 0; i < base; ++i)
            {
                for (int j = 0; j < base; ++j)
                {
                    int x = base_x * base + i;
                    int y = base_y * base + j;
                    if (solved_board[x * side_length + y] != 0)
                    {
                        board_box[base_x * base + base_y] |= 1ULL << (solved_board[x * side_length + y] - 1);
                    }
                }
            }
        }
    }



    // printf("Number of unassigned cells: %u\n", n_unassign);
    // printf("Unassigned cells:\n");
    // for (int i = 0; i < n_unassign; ++i)
    // {
    //     printf("(%u, %u)\n", unassign_ind[i] / side_length, unassign_ind[i] % side_length);
    // }

    uint8_t board[side_length * side_length];
    for (int i = 0; i < side_length * side_length; i++)
    {
        board[i] = solved_board[i];
    }
    // solve sudoku
    #pragma omp parallel num_threads(n_thread)
    {
        #pragma omp single
        {
            solve(board, board_row, board_col, board_box, unassign_ind, n_unassign);
        }
    }




    printf("solution:\n");
    print_sudoku(solved_board, side_length);

    free(solved_board);
    free(unassign_ind);
    return 0;
}