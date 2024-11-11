/**
 * @file stack.c
 * 
 * @brief Implementation of stack operations for managing nodes containing a Latin square board.
 * 
 * This file provides the implementation of functions to initialize, manipulate, and free a stack
 * of nodes. Each node contains a dynamically allocated 2D array representing part of a Latin 
 * square, along with its position in the square. The stack supports basic operations like push, 
 * pop, and printing, as well as memory management functions for safe deallocation.
 * 
 * @authors 
 * - Panagiotis Tsembekis
 * - Rafael Tsekouronas
 */

#include "stack.h"

int initStack(STACK **stack)
{
    *stack = (STACK *)malloc(1 * sizeof(STACK));
    if (stack == NULL)
        return EXIT_FAILURE;

    (*stack)->top = NULL;
    (*stack)->length = 0;
    return EXIT_SUCCESS;
}

int initNode(NODE **newNode, int **board, int row, int col, int size)
{
    *newNode = (NODE *)malloc(sizeof(NODE));
    if (*newNode == NULL) return EXIT_FAILURE;

    (*newNode)->row = row;
    (*newNode)->col = col;
    (*newNode)->arraySize = size;

    // Allocate memory for the 2D array
    (*newNode)->square = (int **)malloc(size * sizeof(int *));
    if ((*newNode)->square == NULL){ // handle improper memory allocation
        perror("Error: Memory allocation for new node's 2D array rows failed.\n");
        free(*newNode);
        *newNode = NULL;
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size; i++)
    {
        (*newNode)->square[i] = (int *)malloc(size * sizeof(int));
        if ((*newNode)->square[i] == NULL)
        {
            perror("Error: Memory allocation for new node's 2D array columns failed.\n");
            for (int j = 0; j < i; j++)
            { // free previously allocated rows
                free((*newNode)->square[j]);
            }
            free((*newNode)->square);
            free(*newNode); // free newNode itself
            *newNode = NULL;
            return EXIT_FAILURE;
        }

        // Copy each element in the row
        for (int j = 0; j < size; j++)
        {
            (*newNode)->square[i][j] = board[i][j];
        }
    }

    (*newNode)->next = NULL; // initialize the next pointer to NULL

    return EXIT_SUCCESS;
}

int push(STACK *stack, NODE *newNode)
{
    if (stack == NULL)
    {
        perror("Unable to push into stack | Stack is NULL.\n");
        return EXIT_FAILURE;
    }

    if (newNode == NULL)
    {
        perror("Unable to push into stack | newNode is NULL.\n");
    }

    newNode->next = stack->top;
    stack->top = newNode;
    (stack->length)++;

    return EXIT_SUCCESS;
}

NODE* pop(STACK *stack)
{
    if (stack == NULL || stack->length == 0)
    {
        perror("Unable to pop from stack | Empty or NULL stack.\n");
        return NULL;
    }

    NODE *temp = stack->top;
    stack->top = temp->next;
    (stack->length)--;

    return temp;
}

bool isEmpty(STACK *stack){
    return (stack->length == 0);
}

void printNode(NODE *node){
    if(node == NULL){
        printf("Can't print node. Node is NULL!\n");
        return;
    }

    // Print top border for the node
    for (int i = 0; i < node->arraySize; i++) {
        printf("+-----");
    }
    printf("+\n");

    // Iterate over the 2D array and print each element with borders
    for (int i = 0; i < node->arraySize; i++) {
        for (int j = 0; j < node->arraySize; j++) {
            if (node->square[i][j] < 0) { // negative values printed inside parentheses
                printf("| (%d) ", -node->square[i][j]);
            } else { // normal values
                printf("|  %d  ", node->square[i][j]);
            }
        }
        printf("|\n"); // end the row

        // Print bottom border for the current row
        for (int k = 0; k < node->arraySize; k++) {
            printf("+-----");
        }
        printf("+\n");

    }
}

void printStack(STACK *stack, int size) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }

    NODE *current = stack->top; // start from top element
    printf("Stack elements (from top to bottom):\n");

    while (current != NULL) {
        printf("Node (row: %d, col: %d):\n", current->row, current->col);
        printNode(current); // print node's contents

        printf("\n"); // separate nodes with a blank line
        current = current->next;
    }

}

void freeNode(NODE *node){
    if (node != NULL) {
        if (node->square != NULL) {
            for (int i = 0; i < node->arraySize; i++) {
                if (node->square[i] != NULL) {
                    free(node->square[i]);
                }
            }
            free(node->square);
        }

    free(node);
    }
}

void freeStack(STACK *stack){
    while (!isEmpty(stack)) {
        NODE *node = pop(stack);
        freeNode(node);
    }

    free(stack);
}