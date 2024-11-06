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
    if (tableau == NULL)
    {
        perror("Failed to initialize puzzle from input file.\n");
        return 1;
    }

    NODE *node = NULL;
    initNode(&node, tableau, 0, 0, size);
    printNode(node);

    // STACK *stack = NULL;
    // if (initStack(&stack) == EXIT_FAILURE)
    // {
    //     perror("Error initializing stack.");
    //     return 1;
    // }

    // Free the 2D array created by readLatinSquare
    for (int i = 0; i < size; i++) {
        free(tableau[i]);
    }
    free(tableau);

    // Free the node created by initNode
    freeNode(node);

    return 0;
}