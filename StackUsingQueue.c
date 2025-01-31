#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

//Queue
typedef struct Node{
    int val;
    struct Node* next;
}Node;

typedef struct Queue{
    Node* front;
    Node* end;
    int size;
}Queue;

void initQueue(Queue* queue){
    queue->front = NULL;
    queue->end = NULL;
    queue->size = 0;
}

int isQueueEmpty(Queue* queue){
    return queue->size == 0;
}

void enqueue(Queue* queue, int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode==NULL){
        printf("\n Queue Overflow!");
        return;
    }

    newNode ->next = NULL;
    newNode->val = value;

    if(isQueueEmpty(queue)){
        queue->front = newNode;
    }else{
        queue->end->next = newNode;
    }
    queue->end = newNode;
    queue->size++;
}

int dequeue(Queue* queue){
    if(isQueueEmpty(queue)){
        printf("Queue is Empty!");
        return INT_MIN;
    }
    Node* temp = queue->front;
    int dequeuedValue = temp->val;
    queue->front = queue->front->next;
    
    if (queue->front == NULL) {
        queue->end = NULL;
    }
    free(temp);
    queue->size--;
    return dequeuedValue;
}

int peekQueue(Queue* queue){
    if(isQueueEmpty(queue)){
        printf("Queue Underflow!");
        return INT_MIN;
    }
    return queue->front->val;
}

int sizeQueue(Queue* queue){
    return queue->size;
}



void freeQueue(Queue* queue){
    Node* current = queue->front;
    while(current){
        Node* temp = current;
        current = current -> next;
        free(temp);
    }
}

//stack
typedef struct Stack
{
    Queue* queue;
}Stack;

void initStack(Stack* s){
    s->queue = malloc(sizeof(Queue));
    initQueue(s->queue);
}
int isEmpty(Stack* s){
    return isQueueEmpty(s->queue);
}

void push(Stack* stack,int value){
    enqueue(stack->queue,value);
    int size = stack->queue->size;
    for(int i=0;i<size-1;i++){
        enqueue(stack->queue, dequeue(stack->queue));
    }
}

int pop(Stack* stack){
    if(isEmpty(stack)){
        printf("Stack Underflow! ");
        return INT_MIN;
    }
    return dequeue(stack->queue);
}

int peek(Stack* stack){
    if(isEmpty(stack)){
        printf("Stack is Empty!\n");
        return INT_MIN;
    }
    return peekQueue(stack->queue);
}

int size(Stack* stack){
    return sizeQueue(stack->queue);
}

void freeStack(Stack* st){
    freeQueue(st->queue);
    free(st->queue);
}
int main(){
    Stack st;
    initStack(&st);
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
    
    printf("Is Stack empty? %s\n", isEmpty(&st) ? "Yes" : "No");

    freeStack(&st);
    return 0;
}