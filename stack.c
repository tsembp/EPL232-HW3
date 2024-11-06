#include "stack.h"

int initStack(STACK **stack){
    *stack = (STACK *) malloc(1 * sizeof(STACK));
    if(stack == NULL) return EXIT_FAILURE;

    (*stack)->top = NULL;
    (*stack)->length = 0;
    return EXIT_SUCCESS;
}

int push(STACK *stack, NODE *newNode){
    if(stack == NULL) {
        perror("Unable to push into stack | Stack is NULL.\n");
        return EXIT_FAILURE;
    }

    if(newNode == NULL){
        perror("Unable to push into stack | newNode is NULL.\n");
    }

    newNode->next = stack->top;
    stack->top = newNode;
    (stack->length)++;

    return EXIT_SUCCESS;
}

int pop(STACK *stack, NODE *retNode){
    if(stack == NULL || stack->length == 0){
        perror("Unable to pop from stack | Empty or NULL stack.\n");
        return EXIT_FAILURE;
    }

    if(retNode == NULL){
        perror("Unable to pop from stack | Return node is NULL.\n");
        return EXIT_FAILURE;
    }

    NODE *temp = stack->top;
    retNode = stack->top;
    stack->top = temp->next;
    (stack->length)--;
    freeNode(temp);

    return EXIT_SUCCESS;
}

void freeNode(NODE *node) {
    if (node != NULL) {
        // Free the 2D array 'square' if it's allocated
        if (node->square != NULL) {
            for (int i = 0; i < node->row; i++) {
                free(node->square[i]);
            }
            free(node->square);
        }
        // Free the node itself
        free(node);
    }
}

void printStack(STACK *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }

    NODE *current = stack->top;
    printf("Stack elements (from top to bottom):\n");
    
    while (current != NULL) {
        printf("Node (row: %d, col: %d):\n", current->row, current->col);
        
        // Iterate over the 2D array and print each element
        for (int i = 0; i < current->row; i++){
            for (int j = 0; j < current->col; j++){
                printf("%d ", current->square[i][j]);
            }
            
            printf("\n"); // New line after each row
        }
        
        printf("\n"); // Separate nodes with a blank line
        current = current->next;
    }
}
