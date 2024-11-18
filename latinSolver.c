/**
 * @file latinSolver.c
 * 
 * @brief Main program for solving a Latin square puzzle using backtracking.
 * 
 * This program initializes a Latin square puzzle from an input file, then attempts
 * to solve it using backtracking with the help of a stack. It displays the outcome
 * of the puzzle solution, including the number of push and pop operations performed.
 * 
 * Usage:
 * ```
 * ./latinSolver <inputFile.txt>
 * ```
 * 
 * @authors
 * - Panagiotis Tsembekis
 * - Rafael Tsekouronas
 * 
 * @bug No known bugs.
 */

#include <stdlib.h>
#include <stdio.h>
#include "file.h"
#include "stack.h"
#include "solver.h"

/**
 * @brief Entry point of the Latin square puzzle solver program.
 * 
 * This function initializes the puzzle from an input file, sets up a stack
 * for backtracking, and calls the `puzzleSolver` function to solve the puzzle.
 * It then outputs the result of the solution attempt, including the number of
 * pushes and pops performed. If any errors occur (e.g., memory allocation failure
 * or an unsolvable puzzle), an appropriate message is displayed.
 * 
 * @param argc The argument count. Should be 2 (program name and input file name).
 * @param argv The argument vector, where `argv[1]` is expected to be the input file name.
 * 
 * @return 0 if the puzzle was solved successfully, 1 if the puzzle was unsolvable or an error occurred.
 */
int main(int argc, char *argv[])
{
    if (argc != 2) // check for improper arguments passed
    {
        printf("Usage:\n");
        printf("./latinSolver <inputFile.txt>\n");
        return 1;
    }

    const char *fileName = argv[1];
    int size;
    int **tableau = readLatinSquare(fileName, &size); // read initial latinsquare and save to tableau
    if(tableau == NULL) // handle improper initialization
    { 
        perror("Failed to initialize puzzle from input file.\n");
        return 1;
    }

    STACK *stack;
    if (initStack(&stack) == EXIT_FAILURE) // handle improper alloaction for stack
    {
        free2DArray(tableau, size); // free previously allocated 2D array
        perror("Error initializing stack.\n");
        return 1;
    }

    int numPush = 0, numPop = 0;
    bool gameResult = puzzleSolver(stack, tableau, size, &numPush, &numPop); // call backtracking funtion to solve

    // Check return value of the solver 
    if(gameResult){
        printf("Congrats! Puzzle solved!\n");
        printf("PUSH NUM: %d\n", numPush);
        printf("POP NUM: %d\n", numPop);
    } else{
        printf("Puzzle not solved. (unsolvable or error)\n");
    }
    
    // Free previously allocated memory blocks
    free2DArray(tableau, size);
    freeStack(stack);

    return 0;
}