/**
 * @file stack.h
 * 
 * @brief Header file for stack operations involving nodes containing a Latin square board.
 * 
 * This file contains function declarations for initializing and managing a stack of nodes,
 * where each node holds a 2D array representing part of a Latin square.
 * 
 * @authors 
 * - Panagiotis Tsembekis
 * - Rafael Tsekouronas
 */

#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @struct NODE
 * @brief Represents a node in the stack containing a Latin square board.
 * 
 * Each node holds a 2D array representing a section of a Latin square,
 * along with its position (row and column) and the size of the array.
 * Nodes are linked together to form a stack.
 */
typedef struct node { 
    int **square; 
    int row; 
    int col; 
    int arraySize;
    struct node *next; 
} NODE; 

/**
 * @struct STACK
 * @brief Represents a stack data structure for managing NODE elements.
 * 
 * The stack tracks the top element and the number of nodes in the stack,
 * allowing for stack operations such as push and pop.
 */
typedef struct stack{ 
    NODE *top;
    int length; 
} STACK; 

/**
 * @brief Initializes the stack.
 * 
 * Allocates memory for a stack and initializes its top pointer and length.
 * 
 * @param stack A double pointer to the stack to be initialized.
 * 
 * @return `EXIT_SUCCESS` on successful initialization, `EXIT_FAILURE` otherwise.
 */
int initStack(STACK **stack);

/**
 * @brief Initializes a new node with a Latin square board and position.
 * 
 * Allocates memory for a new node and its 2D array representing a board.
 * Copies the content of the provided board array into the node.
 * 
 * @param newNode A double pointer to the new node to be initialized.
 * @param board A 2D array representing the board to be copied into the node.
 * @param row The row position in the Latin square.
 * @param col The column position in the Latin square.
 * @param size The size of the Latin square.
 * 
 * @return `EXIT_SUCCESS` on successful initialization, `EXIT_FAILURE` otherwise.
 */
int initNode(NODE **newNode, int **square, int row, int col, int size);

/**
 * @brief Pushes a node onto the stack.
 * 
 * Adds the specified node to the top of the stack.
 * 
 * @param stack A pointer to the stack.
 * @param newNode The node to be pushed onto the stack.
 * 
 * @return `EXIT_SUCCESS` on successful push, `EXIT_FAILURE` if the stack or node is NULL.
 */
int push(STACK *stack, NODE *newNode);

/**
 * @brief Pops a node from the stack.
 * 
 * Removes and returns the node from the top of the stack.
 * 
 * @param stack A pointer to the stack.
 * 
 * @return The popped node, or NULL if the stack is empty or NULL.
 */
NODE* pop(STACK *stack);

/**
 * @brief Checks if the stack is empty.
 * 
 * Determines if the stack contains any elements.
 * 
 * @param stack A pointer to the stack.
 * 
 * @return `true` if the stack is empty, `false` otherwise.
 */
bool isEmpty(STACK *stack);

/**
 * @brief Prints the contents of a node.
 * 
 * Displays the 2D array of the given node with borders around each element.
 * Negative values are shown within parentheses.
 * 
 * @param node A pointer to the node to be printed.
 */
void printNode(NODE *node);

/**
 * @brief Prints the entire stack from top to bottom.
 * 
 * Iterates through each node in the stack and prints its contents.
 * 
 * @param stack A pointer to the stack.
 * @param size The size of the 2D array in each node.
 */
void printStack(STACK *stack, int size);

/**
 * @brief Frees memory allocated for a node.
 * 
 * Deallocates the 2D array within the node and then frees the node itself.
 * 
 * @param node A pointer to the node to be freed.
 */
void freeNode(NODE *node);

/**
 * @brief Frees memory allocated for the entire stack.
 * 
 * Pops and frees each node in the stack, then frees the stack itself.
 * 
 * @param stack A pointer to the stack to be freed.
 */
void freeStack(STACK *stack);

#endif // STACK_H