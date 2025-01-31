#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define LOAD_FACTOR 0.75

typedef struct Stack{
    int* arr;
    int top;
    int capacity;
}Stack;

void push(Stack* stack, int value){
    if(stack->top>=stack->capacity*LOAD_FACTOR){
        stack->arr = (int*)realloc(stack->arr,(stack->capacity)*2*sizeof(int));
        if(stack->arr){
            printf("\n Memory Allocation Failed!");
            exit(1);
        }
        stack->capacity *= 2;
    }
    stack->arr[++stack->top] = value;
}
int isEmpty(Stack* stack){
    return stack->top < 0;
}
int pop(Stack* stack){
    if(isEmpty(stack)){
        printf("Stack is Empty!");
        return INT_MIN;
    }
    return stack->arr[(stack->top)--];
}

int peek(Stack* stack){
    if(isEmpty(stack)){
        printf("Stack is Empty!");
        return INT_MIN;
    }
    return stack->arr[stack->top];
}
int size(Stack* stack){
    return stack->top + 1;
}

void initStack(Stack* stack, int capacity){
    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (int*)malloc(capacity*sizeof(int));
}

void freeStack(Stack* stack){
    free(stack->arr);
}
int main(){
    Stack st;
    initStack(&st,30);
    push(&st, 150);
    push(&st, 20);
    push(&st, 301);
    push(&st, -98);
    
    printf("Top element: %d\n", peek(&st));
    printf("Stack size: %d\n", size(&st));
    
    printf("Popped: %d\n", pop(&st));
    printf("Popped: %d\n", pop(&st));
    printf("Popped: %d\n", pop(&st));
    printf("Popped: %d\n", pop(&st));
    printf("Popped: %d\n", pop(&st));
    
    printf("Is stack empty? %s\n", isEmpty(&st) ? "Yes" : "No");

    freeStack(&st);
    return 0;
}