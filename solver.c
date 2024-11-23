/**
 * @file solver.c
 *
 * @brief Implementation of the Latin square puzzle-solving algorithm using backtracking and a stack.
 *
 * This file contains functions that attempt to solve a Latin square puzzle by placing numbers
 * while checking each move against the rules of the puzzle. It uses backtracking with a stack
 * to keep track of placements and to revert to previous states when necessary.
 *
 * The main functions include `puzzleSolver` to drive the solving process, `attemptPlacement`
 * to place numbers while following constraints, and helper functions `isSafe` and `findEmptyPosition`
 * to assist in validating placements and locating empty positions.
 *
 * @authors
 * - Panagiotis Tsembekis
 * - Rafael Tsekouronas
 *
 * @bug No known bugs.
 */

#include "solver.h"
#include <string.h>

/**
 * @brief Attempts to place a number in the next empty cell of the Latin square.
 *
 * This function acts as a helper function for puzzleSolver. It tries to place numbers sequentially in the specified cell,
 * skipping those that have already been tried. If a valid placement is found,
 * it pushes the state onto the stack.
 *
 * @param stack The stack used for storing states of the puzzle.
 * @param square The current state of the Latin square as a 2D array.
 * @param size The size of the Latin square.
 * @param numPush Pointer to the counter tracking the number of pushes to the stack.
 * @param stepsNum Pointer to the counter tracking the total steps taken.
 * @param rowIndex Pointer to the current row being processed.
 * @param colIndex Pointer to the current column being processed.
 * @param triedNumbers Array indicating numbers that have already been attempted for the current cell.
 * @param startIndex The starting number to attempt placement.
 *
 * @return `true` if a placement was successful, `false` otherwise.
 *
 * @see puzzleSolver(STACK *stack, int **square, int size, int *numPush, int *numPop) For the main function that calls this helper.
 */
bool attemptPlacement(STACK *stack, int **square, int size, int *numPush, int *stepsNum, int *rowIndex, int *colIndex, int *triedNumbers, int startIndex)
{
    for (int i = startIndex; i <= size; i++) // begin from number given at `startingIndex`
    {
        if (triedNumbers[i] == 1)
            continue; // skip numbers that have been tried

        if (isSafe(square, *rowIndex, *colIndex, i, size)) // check if number adheres to rules of the game
        {
            // Initialize a new node for the new current state
            NODE *node;
            if (initNode(&node, square, *rowIndex, *colIndex, size) == EXIT_FAILURE)
            {
                return false; // handle memory allocation failure
            }

            // Insert the new value
            node->row = *rowIndex;
            node->col = *colIndex;
            node->square[*rowIndex][*colIndex] = i;

            // Push the new state onto the stack
            printf("PUSH: STEP %d\n", *stepsNum);
            push(stack, node);
            printNode(stack->top);
            (*numPush)++;
            (*stepsNum)++;

            // Update `square` by modifying its contents (no need to change `square` itself)
            for (int i = 0; i < size; i++)
            {
                memcpy(square[i], node->square[i], size * sizeof(int)); // copy row of `square` to the node's square array
            }

            memset(triedNumbers, 0, (size + 1) * sizeof(int)); // reset tried numbers for next function call
            return true;                                       // successfull placement
        }
        else // not safe insertion
        {
            triedNumbers[i] = 1; // mark this number as tried
        }
    }

    return false; // no placement was possible
}

// Main solver function for automatically solving the latin square
bool puzzleSolver(STACK *stack, int **square, int size, int *numPush, int *numPop)
{
    int stepsNum = 1, rowIndex = -1, colIndex = -1;
    int *triedNumbers = (int *)calloc(size + 1, sizeof(int)); // dynamic array initialized to 0

    while (findEmptyPosition(square, size, &rowIndex, &colIndex)) // while `square` is not filled
    {
        // Attempt placemenet
        bool placed = attemptPlacement(stack, square, size, numPush, &stepsNum, &rowIndex, &colIndex, triedNumbers, 1);

        if (!placed) // if no number [1,size] managed to be inserted, we need to backtrack
        {
            while (!placed) // backtrack until we can insert a new number
            {
                if (isEmpty(stack)) // if empty stack is reached, we have no possible solution
                {
                    free(triedNumbers);
                    return false; // no solution exists
                }

                // Print and pop current state
                printf("POP: STEP %d\n", stepsNum);
                printNode(stack->top);
                NODE *poppedNode = pop(stack);

                // Retrieve index and value of last inserted number
                rowIndex = poppedNode->row;
                colIndex = poppedNode->col;
                int lastNumTried = poppedNode->square[rowIndex][colIndex];
                square[rowIndex][colIndex] = 0; // reset the cell

                freeNode(poppedNode); // free last state
                stepsNum++;
                (*numPop)++;

                // Reset `triedNumbers` and mark `lastNumTried` as tried
                memset(triedNumbers, 0, (size + 1) * sizeof(int));
                triedNumbers[lastNumTried] = 1;

                // Attempt to place the next number starting from `lastNumTried + 1`
                placed = attemptPlacement(stack, square, size, numPush, &stepsNum, &rowIndex, &colIndex, triedNumbers, lastNumTried + 1);
            }
        }
    }

    free(triedNumbers);
    return true;
}

// Checks if placing num at [row][col] matches the game's rules
bool isSafe(int **square, int row, int col, int num, int size)
{
    // Step 1: Check row condition - One element 'num' per row
    for (int j = 0; j < size; j++)
    {
        if (abs(square[row][j]) == num) // handle both positive and negative (pre-given) values
        {
            printf("\nError: Illegal value insertion! | Can't insert %d at (%d,%d).\n", num, row, col);
            return false;
        }
    }

    // Step 2: Check column condition - One element 'num' per column
    for (int i = 0; i < size; i++)
    {
        if (abs(square[i][col]) == num) // handle both positive and negative (pre-given) values
        {
            printf("\nError: Illegal value insertion! | Can't insert %d at (%d,%d).\n", num, row, col);
            return false;
        }
    }

    return true;
}

// Find the first empty cell in the `square`
bool findEmptyPosition(int **square, int size, int *row, int *col)
{
    // Iterate through the whole array
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (square[i][j] == 0) // =0 indicates empty cell
            {
                // Set values for row and column and return true
                *row = i;
                *col = j;
                return true;
            }
        }
    }

    return false; // if condition is reached -> solved! :)
}

#ifdef DEBUG_SOLVER

int main()
{
    int size = 4; // Example size for the Latin square
    int **square = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        square[i] = (int *)calloc(size, sizeof(int)); // Initialize all cells to 0
    }

    // Example pre-filled Latin square setup (0 indicates an empty cell)
    square[0][0] = 1;
    square[0][1] = 2;
    square[1][0] = 2;
    square[1][1] = 1;

    printf("Initial Latin square:\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d ", square[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Initialize the stack
    STACK *stack = NULL;
    if (initStack(&stack) != EXIT_SUCCESS)
    {
        printf("Failed to initialize stack.\n");
        free2DArray(square, size);
        return 1;
    }

    int numPush = 0, numPop = 0;
    // Solve the puzzle
    if (puzzleSolver(stack, square, size, &numPush, &numPop))
    {
        printf("Latin square solved successfully:\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%d ", square[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Failed to solve the Latin square.\n");
    }

    // Cleanup
    free2DArray(square, size);
    freeStack(stack);

    return 0;
}
#endif
