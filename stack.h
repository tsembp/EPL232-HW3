#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node { 
    int **square; 
    int row; 
    int col; 
    int arraySize;
    struct node *next; 
} NODE; 

typedef struct stack{ 
    NODE *top;
    int length; 
} STACK; 

int initStack(STACK **stack);
int initNode(NODE **newNode, int **square, int row, int col, int size);
int push(STACK *stack, NODE *newNode);
NODE* pop(STACK *stack);
void freeNode(NODE *node);
bool isEmpty(STACK *stack);
void printStack(STACK *stack, int size);
void printNode(NODE *node);


#endif // STACK_H