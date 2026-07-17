#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack *stack_create(){
    Stack *stack = malloc(sizeof(Stack));
    if(stack == NULL) return NULL;
    stack->top = NULL;
    return stack;
}

void stack_destroy(Stack *stack, destroy_data_func destroy_data){
    if(stack == NULL) return;
    while(stack->top != NULL){
        Node *temp = stack->top;
        stack->top = stack->top->next;
        if(destroy_data != NULL) destroy_data(temp->data);
        free(temp);
    }
    free(stack);
}

void stack_push(Stack *stack, void *item){
    if(stack == NULL) return;
    Node *new_node = malloc(sizeof(Node));
    if(new_node == NULL) return;
    new_node->data = item;
    new_node->next = stack->top;
    stack->top = new_node;
}

void *stack_pop(Stack *stack){
    if(stack == NULL || stack->top == NULL) return NULL;
    Node *temp = stack->top;
    void *item = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return item;
}

void *stack_peek(Stack *stack){
    if(stack == NULL || stack->top == NULL) return NULL;
    return stack->top->data;
}

bool stack_is_empty(Stack *stack){
    if(stack == NULL) return true;
    return stack->top == NULL;
}