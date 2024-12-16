#include "stack.h"

static void resize_stack(Stack *self) {
    if (self->capacity >= INT_MAX / 2) {
        fprintf(stderr, "Error: Stack size exceeds maximum capacity.\n");
        exit(EXIT_FAILURE);
    }

    int new_capacity = self->capacity * 2;
    if (new_capacity > INT_MAX) {
        new_capacity = INT_MAX;
    }

    int *new_data = (int *)realloc(self->data, new_capacity * sizeof(int));
    if (!new_data) {
        fprintf(stderr, "Error: Memory allocation failed during stack resizing.\n");
        exit(EXIT_FAILURE);
    }

    self->data = new_data;
    self->capacity = new_capacity;
}


Stack *create_stack(int initial_capacity){
        if (initial_capacity <= 0) {
        fprintf(stderr, "Error: Initial capacity must be greater than zero.\n");
        exit(EXIT_FAILURE);
    }

    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack) {
        fprintf(stderr, "Error: Memory allocation failed for stack.\n");
        exit(EXIT_FAILURE);
    }

    stack->data = (int *)malloc(initial_capacity * sizeof(int));
    if (!stack->data) {
        fprintf(stderr, "Error: Memory allocation failed for stack data.\n");
        free(stack);
        exit(EXIT_FAILURE);
    }

    stack->capacity = initial_capacity;
    stack->top = 0;

    stack->push = push;
    stack->pop = pop;
    stack->peek = peek;
    stack->is_empty = is_empty;
    stack->destroy = destroy;

    return stack;
}

void push(Stack* self, int value){
    if(self->top >= self->capacity){
        resize_stack(self);
    }
    self->data[self->top++] = value;
}

int pop(Stack* self){
    if(self->top <= 0){
        fprintf(stderr, "Error: Attempt to pop from an empty stack.\n");
        exit(EXIT_FAILURE);
    }
    return self->data[--self->top];
}

int peek(Stack *self) {
    if (self->top == 0) {
        fprintf(stderr, "Error: Attempt to peek from an empty stack.\n");
        exit(EXIT_FAILURE);
    }
    return self->data[self->top - 1];
}

int is_empty(Stack *self) {
    return self->top == 0;
}

void destroy(Stack *self) {
    free(self->data);
    self->data = NULL;
    self->capacity = 0;
    self->top = 0;
}

