#include <stdlib.h>
#include <stdio.h>
#include "file.h"
#include "stack.h"
#include "solver.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage:\n");
        printf("./latinSolver <inputFile.txt>\n");
        return 1;
    }

    const char *fileName = argv[1];
    int size;
    int **tableau = readLatinSquare(fileName, &size);
    if(tableau == NULL){
        perror("Failed to initialize puzzle from input file.\n");
        return 1;
    }

    STACK *stack;
    if (initStack(&stack) == EXIT_FAILURE)
    {
        free2DArray(tableau, size);
        perror("Error initializing stack.");
        return 1;
    }

    int numPush = 0, numPop = 0;
    bool gameResult = puzzleSolver(stack, tableau, size, &numPush, &numPop);

    // Possibly make it 0=good 1=unsolved 2=error allocate
    if(gameResult){
        printf("Congrats! Puzzle solved!\n");
        printf("PUSH NUM: %d\n", numPush);
        printf("POP NUM: %d\n", numPop);
    } else{
        printf("Puzzle not solved. (unsolvable or error)\n");
    }
    
    freeStack(stack);

    return 0;
}