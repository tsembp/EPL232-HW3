#ifndef STACK_H
#define STACK_H
#include <stdio.h>
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

int push(STACK *stack, NODE newNode);
int pop(STACK *stack, NODE *retVal);
bool isEmpty(STACK *stack);
void free(NODE *node);

#endif // STACK_H