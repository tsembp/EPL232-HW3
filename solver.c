#include "solver.h"
#include "stack.h"

bool puzzleSolver(STACK *stack, int **square, int size, int *numPush, int *numPop)
{
    int stepsNum = 1, rowIndex = -1, colIndex = -1;
    while(findEmptyPosition(square, size, rowIndex, colIndex)){ // while board is not filled
        for(int i = 1; i <= size; i++){
            if(isSafe(square, rowIndex, colIndex, i, size)){
                // Initialize new node for new current state
                NODE *node  = NULL;
                if(initNode(node, square, rowIndex, colIndex, size) == EXIT_FAILURE){
                    freeStack(stack);
                    // free 2D array NOMIZO
                    return false;
                }

                // Insert new value
                node->row = rowIndex;
                node->col = colIndex;
                node->square[rowIndex][colIndex] = i;

                // Push new state in stack
                printf("PUSH: STEP %d\n", stepsNum);
                push(stack, node);
                (*numPush)++;
                stepsNum++;

            } else{ // if number attempted to insert raises error..
                // Print current state (stack->top)
                printf("POP: STEP %d\n", stepsNum);
                printNode(stack->top);

                // Pop current state
                NODE *poppedNode = pop(stack);
                i = poppedNode->square[poppedNode->row][poppedNode->col] + 1; // modify i to continue checking from current num + 1
                free(poppedNode);

                stepsNum++;
                (*numPop)++;
            }
        }
    }
    
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