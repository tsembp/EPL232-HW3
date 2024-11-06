#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node { 
    int **square; 
    int row; 
    int col; 
    struct node *next; 
} NODE; 

typedef struct stack{ 
    NODE *top;
    int length; 
} STACK; 

int initStack(STACK **stack);
int initNode(NODE **newNode, int **square, int row, int col, int size);
int push(STACK *stack, NODE *newNode);
int pop(STACK *stack, NODE *retVal);
void freeNode(NODE *node);
void printStack(STACK *stack);


#endif // STACK_H