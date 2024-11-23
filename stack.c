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
 *
 * @bug No known bugs.
 */

#include "stack.h"
#include "file.h"

int initStack(STACK **stack)
{
    *stack = (STACK *)malloc(1 * sizeof(STACK));
    if (stack == NULL) // handle improper memory allocation
    {
        return EXIT_FAILURE;
    }

    // Initialize stack's values
    (*stack)->top = NULL;
    (*stack)->length = 0;
    return EXIT_SUCCESS;
}

int initNode(NODE **newNode, int **board, int row, int col, int size)
{
    *newNode = (NODE *)malloc(sizeof(NODE));
    if (*newNode == NULL) // handle improper memory allocation
    {
        return EXIT_FAILURE;
    }

    // Assign values to `newNode`
    (*newNode)->row = row;
    (*newNode)->col = col;
    (*newNode)->arraySize = size;

    // Allocate memory for the 2D array
    (*newNode)->square = (int **)malloc(size * sizeof(int *));
    if ((*newNode)->square == NULL)
    { // handle improper memory allocation
        perror("Error: Memory allocation for new node's 2D array rows failed.\n");
        free(*newNode); // free previously allocated space for node
        *newNode = NULL;
        return EXIT_FAILURE;
    }

    // Allocate space for columns for 2D array of `newNode`
    for (int i = 0; i < size; i++)
    {
        (*newNode)->square[i] = (int *)malloc(size * sizeof(int));
        if ((*newNode)->square[i] == NULL) // handle improper memory allocation
        {
            perror("Error: Memory allocation for new node's 2D array columns failed.\n");
            // Free previously allocated space for 2D array and `node`
            free2DArray((*newNode)->square, i);
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
    if (stack == NULL) // handle edge case of null stack
    {
        perror("Unable to push into stack | Stack is NULL.\n");
        return EXIT_FAILURE;
    }

    if (newNode == NULL) // handle edge case of null node passed in
    {
        perror("Unable to push into stack | newNode is NULL.\n");
    }

    // Add node to stack
    newNode->next = stack->top;
    stack->top = newNode;
    (stack->length)++;

    return EXIT_SUCCESS;
}

NODE *pop(STACK *stack)
{
    if (stack == NULL || stack->length == 0) // handle edge case of empty/null stack
    {
        perror("Unable to pop from stack | Empty or NULL stack.\n");
        return NULL;
    }

    // Remove node at stack->top
    NODE *temp = stack->top;
    stack->top = temp->next;
    (stack->length)--;

    return temp;
}

bool isEmpty(STACK *stack)
{
    return (stack->length == 0); // if length = 0 => empty stack
}

void printNode(NODE *node)
{
    if (node == NULL) // handle edge case of null node
    {
        printf("Can't print node. Node is NULL!\n");
        return;
    }

    // Print top border for the node
    for (int i = 0; i < node->arraySize; i++)
    {
        printf("+-----");
    }
    printf("+\n");

    // Iterate over the 2D array and print each element with borders
    for (int i = 0; i < node->arraySize; i++)
    {
        for (int j = 0; j < node->arraySize; j++)
        {
            if (node->square[i][j] < 0)
            { // negative values printed inside parentheses
                printf("| (%d) ", -node->square[i][j]);
            }
            else
            { // normal values
                printf("|  %d  ", node->square[i][j]);
            }
        }
        printf("|\n"); // end the row

        // Print bottom border for the current row
        for (int k = 0; k < node->arraySize; k++)
        {
            printf("+-----");
        }
        printf("+\n");
    }
}

void printStack(STACK *stack, int size)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty!\n");
        return;
    }

    NODE *current = stack->top; // start from top element
    printf("Stack elements (from top to bottom):\n");

    while (current != NULL)
    {
        printf("Node (row: %d, col: %d):\n", current->row, current->col);
        printNode(current); // print node's contents

        printf("\n"); // separate nodes with a blank line
        current = current->next;
    }
}

void freeNode(NODE *node)
{
    if (node != NULL)
    {
        if (node->square != NULL)
        {
            free2DArray(node->square, node->arraySize); // free 2D array
        }

        free(node); // free node itself
    }
}

void freeStack(STACK *stack)
{
    while (!isEmpty(stack))
    {
        NODE *node = pop(stack); // pop top node
        freeNode(node);          // free top node
    }

    free(stack);
}

#ifdef DEBUG_STACK

int main()
{
    STACK *stack = NULL;

    // Initialize the stack
    if (initStack(&stack) != EXIT_SUCCESS)
    {
        printf("Failed to initialize stack.\n");
        return 1;
    }
    printf("Stack initialized successfully.\n");

    // Create a 2D array to represent a Latin square node
    int size = 3;
    int **board = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        board[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++)
        {
            board[i][j] = (i + j + 1) % size + 1; // Simple Latin square
        }
    }

    // Create and push nodes into the stack
    for (int i = 0; i < 3; i++)
    {
        NODE *node = NULL;
        if (initNode(&node, board, i, i, size) != EXIT_SUCCESS)
        {
            printf("Failed to initialize node %d.\n", i);
        }
        else
        {
            printf("Node %d initialized successfully.\n", i);
            push(stack, node);
            printf("Node %d pushed to stack.\n", i);
        }
    }

    // Print the stack
    printf("\nCurrent stack:\n");
    printStack(stack, size);

    // Pop and print nodes
    for (int i = 0; i < 3; i++)
    {
        NODE *node = pop(stack);
        if (node != NULL)
        {
            printf("\nPopped node (row: %d, col: %d):\n", node->row, node->col);
            printNode(node);
            freeNode(node);
        }
        else
        {
            printf("Failed to pop node %d.\n", i);
        }
    }

    // Check if the stack is empty
    if (isEmpty(stack))
    {
        printf("\nStack is now empty.\n");
    }
    else
    {
        printf("\nStack is not empty.\n");
    }

    // Free the stack
    freeStack(stack);
    printf("Stack freed successfully.\n");

    // Free the test board
    free2DArray(board, size);

    return 0;
}
#endif