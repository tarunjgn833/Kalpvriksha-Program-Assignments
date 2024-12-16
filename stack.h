#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Stack
{
    int *data;
    int capacity;
    int top;

    void (*push)(struct Stack *self, int value);
    int (*pop)(struct Stack *self);
    int (*peek)(struct Stack *self);
    int (*is_empty)(struct Stack *self);
    void (*destroy)(struct Stack *self);
} Stack;

void push(Stack *self, int value);
int pop(Stack *self);
int peek(Stack *self);
int is_empty(Stack *self);
void destroy(Stack *self);
Stack *create_stack(int initial_capacity);

#endif
