#include "solver.h"
#include "stack.h"

bool puzzleSolver(STACK *stack, int **square, int size)
{
}

// Checks if placing num at [row][col] matches the game's rules
bool isSafe(int **square, int row, int col, int num, int size)
{
    // Step 1: Check row condition - One element 'num' per row
    for (int j = 0; j < size; j++)
    {
        if (abs(square[row][j]) == num)
        {
            printf("\nError: Illegal value insertion! | Value already exists in row %d!\n", row);
            return false;
        }
    }

    // Step 2: Check column condition - One element 'num' per column
    for (int i = 0; i < size; i++)
    {
        if (abs(square[i][col]) == num)
        {
            printf("\nError: Illegal value insertion! | Value already exists in column %d!\n", col);
            return false;
        }
    }

    return true;
}

bool findEmptyPosition(int **square, int size, int *row, int *col)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (square[i][j] == 0)
            {
                *row = i;
                *col = j;
                return true;
            }
        }
    }

    return false; // if condition is reached -> solved! :)
}