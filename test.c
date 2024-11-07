#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int** create2DArray(int size, int startValue) {
    int** array = (int**)malloc(size * sizeof(int*));
    if (array == NULL) {
        perror("Failed to allocate memory for 2D array");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        array[i] = (int*)malloc(size * sizeof(int));
        if (array[i] == NULL) {
            perror("Failed to allocate memory for 2D array row");
            for (int j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < size; j++) {
            // Generate values within the range [-9, 9]
            int value = (startValue++ % 19) - 9; // Produces values from -9 to 9
            array[i][j] = value;
        }
    }

    return array;
}

int main() {
    STACK *stack;
    initStack(&stack);

    // Create and push 2D nodes with the same array size (5x5) onto the stack
    int arraySize = 5;
    for (int i = 0; i < 3; i++) { // Generate 3 nodes for testing
        int** array = create2DArray(arraySize, 1 + (i * arraySize * arraySize)); // Create a 5x5 matrix with distinct start values
        NODE *node;
        initNode(&node, array, arraySize, arraySize, arraySize); // Initialize the node 
        push(stack, node); // Push the node onto the stack
        printf("Pushed node with %dx%d matrix\n", arraySize, arraySize);

        // Free the temporary array used for node creation
        for (int j = 0; j < arraySize; j++) {
            free(array[j]);
        }
        free(array);
    }

    // Display the current state of the stack
    printf("\nCurrent stack state:\n");
    printStack(stack, arraySize);

    // Test pop operation
    printf("\nPopping nodes from the stack...\n");
    NODE *poppedNode;
    while (!isEmpty(stack)) {
        poppedNode = pop(stack);
        if (poppedNode != NULL) {
            printf("Popped node with row=%d, col=%d\n", poppedNode->row, poppedNode->col);
            printNode(poppedNode); // too many arguments with arraysize

            // Free the popped node's 2D array and the node itself
            for (int i = 0; i < poppedNode->row; i++) {
                free(poppedNode->square[i]);
            }
            free(poppedNode->square);
            free(poppedNode);
        }
    }

    // Check if the stack is empty
    if (isEmpty(stack)) {
        printf("\nStack is now empty.\n");
    } else {
        printf("\nStack is not empty.\n");
    }

    free(stack); // Free the stack structure itself
    return 0;
}
