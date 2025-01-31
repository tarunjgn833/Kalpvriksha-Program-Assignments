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
int isStackEmpty(Stack* stack){
    return stack->top < 0;
}
int pop(Stack* stack){
    if(isStackEmpty(stack)){
        printf("Stack is Empty!");
        return INT_MIN;
    }
    return stack->arr[(stack->top)--];
}

int peekStack(Stack* stack){
    if(isStackEmpty(stack)){
        printf("Stack is Empty!");
        return INT_MIN;
    }
    return stack->arr[stack->top];
}
int sizeStack(Stack* stack){
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

//Qeueue
typedef struct Queue
{
    Stack* stack1;
    Stack* stack2;
}Queue;

void initQueue(Queue* queue, int capacity){
    queue->stack1 = malloc(sizeof(Stack));
    queue->stack2 = malloc(sizeof(Stack));
    initStack(queue->stack1,capacity);
    initStack(queue->stack2,capacity);
}

int isEmpty(Queue* queue){
    return isStackEmpty(queue->stack1);
}

void enqueue(Queue* queue, int value){
    while (!isStackEmpty(queue->stack1)) {
        push(queue->stack2,pop(queue->stack1));
    }

     push(queue->stack1,value);
 
    while (!isStackEmpty(queue->stack2)) {
        push(queue->stack1,pop(queue->stack2));
    }
};

int dequeue(Queue* queue){
    if(isStackEmpty(queue->stack1)){
        printf("Queue is Empty!");
        return INT_MIN;
    }
    return pop(queue->stack1);
}

int peek(Queue* queue){
    if(isStackEmpty(queue->stack1)){
        printf("Queue is Empty!");
        return INT_MIN;
    }
    return peekStack(queue->stack1);
}

int size(Queue* queue){
    return sizeStack(queue->stack1);
}

void freeQueue(Queue* queue){
    freeStack(queue->stack1);
    freeStack(queue->stack2);
    free(queue->stack1);
    free(queue->stack2);
}

int main(){
    Queue st;
    initQueue(&st,50);
    enqueue(&st, 150);
    enqueue(&st, 20);
    enqueue(&st, 301);
    enqueue(&st, -98);
    
    printf("Front element: %d\n", peek(&st));
    printf("Queue size: %d\n", size(&st));
    
    
    printf("Dequeued: %d\n", dequeue(&st));
    printf("Dequeued: %d\n", dequeue(&st));
    printf("Dequeued: %d\n", dequeue(&st));
    printf("Dequeued: %d\n", dequeue(&st));
    printf("Dequeued: %d\n", dequeue(&st));
    
    printf("Is queue empty? %s\n", isEmpty(&st) ? "Yes" : "No");

    freeQueue(&st);
    return 0;
}