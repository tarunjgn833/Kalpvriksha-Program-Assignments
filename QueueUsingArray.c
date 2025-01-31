#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define LOAD_FACTOR 0.75

typedef struct Queue{
    int* arr;
    int front;
    int capacity;
    int end;
}Queue;

void initQueue(Queue* queue, int capacity){
    queue->capacity = capacity;
    queue->front = -1;
    queue->arr = (int*)malloc(capacity*sizeof(int));
    queue->end = -1;
}

void enqueue(Queue* queue, int value){
    if(queue->end>=queue->capacity*LOAD_FACTOR){
        queue->arr = (int*)realloc(queue->arr,(queue->capacity)*2*sizeof(int));
        if(queue->arr){
            printf("\n Memory Allocation Failed!");
            exit(1);
        }
        queue->capacity *= 2;
    }
    if(queue->front == -1){
        queue->front++;
    }
    queue->arr[++queue->end] = value;
}
int isEmpty(Queue* queue){
    return queue->front == -1;
}
int dequeue(Queue* queue){
    if(isEmpty(queue)){
        printf("Queue is Empty!");
        return INT_MIN;
    }
    int dequeuedValue = queue->arr[queue->front];
    if (queue->front == queue->end) {
        queue->front = queue->end = -1;
    } else {
        queue->front++;
    }
    return dequeuedValue;
}

int peek(Queue* queue){
    if(isEmpty(queue)){
        printf("Queue is Empty!");
        return INT_MIN;
    }
    return queue->arr[queue->front];
}
int size(Queue* queue){
    if(isEmpty(queue))return 0;
    return queue->end - queue->front +1;
}


void freeQueue(Queue* queue){
    free(queue->arr);
}
int main(){
    Queue st;
    initQueue(&st,50);
    enqueue(&st, 150);
    enqueue(&st, 20);
    enqueue(&st, 301);
    enqueue(&st, -98);
    
    printf("First element: %d\n", peek(&st));
    printf("Queue Size: %d\n", size(&st));
    
    printf("Dequeued: %d\n", dequeue(&st));
    printf("Dequeued: %d\n", dequeue(&st));
    printf("Dequeued: %d\n", dequeue(&st));
    printf("Dequeued: %d\n", dequeue(&st));
    printf("Dequeued: %d\n", dequeue(&st));
    
    printf("Is Queue empty? %s\n", isEmpty(&st) ? "Yes" : "No");

    freeQueue(&st);
    return 0;
}