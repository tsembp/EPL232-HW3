#include "solver.h"
#include "stack.h"

bool puzzleSolver(STACK *stack, int **square, int size)
{
    // thoughts:
    // 1. this func should also take as parameters (int *num_push, int *num_pop)
    // so when the puzzle is solved (if no problem in .txt file) the main can print the results
    // 2. do-while{structure} -> while(findEmptyPosition)
    // this can be done by not finding another empty position
    // also: 
    // 3. we should keep track of the num that is inserted (using the positions from the node's struct)
    // so we can continue searching the next correct num to be inserted
    // so basically if the next cell cannot find a number, we should keep the current state's last inserted number position and value
    // and try the next one (for loop) while the num <= size


    // Base case: this method has been called from main
    // 1. find the first empty cell
    // 2. find the num that respects the rull of the game from [1 - size]
    // 3. insert the number to the array and push the new array to the stack
    // 4. if you don't find the num here (base case) it means there's an issue with the way the puzzle was firstly given in the .txt file and it's unsolvable
    
    // Start the automatic process: (repeat)
    // 1. find the next empty cell
    // 2. find a num that respects the rules of the game
    // 3. insert the num to the array and push new onto the stack
    // 4. if you can't find a num pop the prev state of the puzzle
    // note : based on the pdf if the num is not found
    // we should print the current state of the array
    // and afterwards remove it (pg. 7)

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