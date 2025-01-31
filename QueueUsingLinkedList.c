#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define LOAD_FACTOR 0.75

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

int isEmpty(Queue* queue){
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

    if(isEmpty(queue)){
        queue->front = newNode;
    }else{
        queue->end->next = newNode;
    }
    queue->end = newNode;
    queue->size++;
}

int dequeue(Queue* queue){
    if(isEmpty(queue)){
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

int peek(Queue* queue){
    if(isEmpty(queue)){
        printf("Queue Underflow!");
        return INT_MIN;
    }
    return queue->front->val;
}

int size(Queue* queue){
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
int main(){
    Queue st;
    initQueue(&st);
    enqueue(&st, 150);
    enqueue(&st, 20);
    enqueue(&st, 301);
    enqueue(&st, -98);
    
    printf("First element: %d\n", peek(&st));
    printf("Queue size: %d\n", size(&st));
    
    printf("Dequeued: %d\n", dequeue(&st));
    printf("Dequeued: %d\n", dequeue(&st));
    printf("Dequeued: %d\n", dequeue(&st));
    printf("Dequeued: %d\n", dequeue(&st));
    printf("Dequeued: %d\n", dequeue(&st));
    
    printf("Is Queue empty? %s\n", isEmpty(&st) ? "Yes" : "No");

    freeQueue(&st);
    return 0;
}