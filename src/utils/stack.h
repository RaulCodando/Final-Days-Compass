#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

typedef void (*destroy_data_func)(void *data);

Stack *stack_create();
void stack_destroy(Stack *stack, destroy_data_func destroy_data);
void stack_push(Stack *stack, void *item);
void *stack_pop(Stack *stack);
void *stack_peek(Stack *stack);
bool stack_is_empty(Stack *stack);

#endif // STACK_H