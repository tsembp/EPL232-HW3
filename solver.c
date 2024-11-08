#include "solver.h"
#include "stack.h"
#include <string.h>

bool attemptPlacement(STACK *stack, int **square, int size, int *numPush, int *stepsNum, int *rowIndex, int *colIndex, int *triedNumbers, int startIndex) {
    for (int i = startIndex; i <= size; i++) {
        if (triedNumbers[i] == 1) continue; // Skip numbers that have been tried

        if (isSafe(square, *rowIndex, *colIndex, i, size)) {
            // Initialize a new node for the new current state
            NODE *node;
            if (initNode(&node, square, *rowIndex, *colIndex, size) == EXIT_FAILURE) {
                return false; // Handle memory allocation failure
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
            for (int i = 0; i < size; i++) {
                memcpy(square[i], node->square[i], size * sizeof(int));
            }
            memset(triedNumbers, 0, (size + 1) * sizeof(int)); // Reset tried numbers for the next cell
            return true; // Placement was successful
        } else {
            triedNumbers[i] = 1; // Mark this number as tried
        }
    }

    return false; // No placement was possible
}


bool puzzleSolver(STACK *stack, int **square, int size, int *numPush, int *numPop)
{
    int stepsNum = 1, rowIndex = -1, colIndex = -1;
    int *triedNumbers = (int *)calloc(size + 1, sizeof(int)); // dynamic array initialized to 0

    while (findEmptyPosition(square, size, &rowIndex, &colIndex))
    { // while board is not filled
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

                freeNode(poppedNode);
                poppedNode->square = NULL;
                square[rowIndex][colIndex] = 0; // reset the cell
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
        if (abs(square[row][j]) == num)
        {
            printf("\nError: Illegal value insertion! | Can't insert %d at (%d,%d).\n", num, row, col);
            return false;
        }
    }

    // Step 2: Check column condition - One element 'num' per column
    for (int i = 0; i < size; i++)
    {
        if (abs(square[i][col]) == num)
        {
            printf("\nError: Illegal value insertion! | Can't insert %d at (%d,%d).\n", num, row, col);
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