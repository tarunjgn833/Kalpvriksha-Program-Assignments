#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define LOAD_FACTOR 0.75

typedef struct Node{
    int val;
    struct Node* next;
}Node;

typedef struct Stack{
    Node* top;
    int size;
}Stack;

void initStack(Stack* stack){
    stack->top = NULL;
    stack->size = 0;
}

void push(Stack* stack, int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode==NULL){
        printf("\n Stack Overflow!");
        return;
    }
    newNode->val = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

int isEmpty(Stack* stack){
    return stack->size == 0;
}

int pop(Stack* stack){
    if(isEmpty(stack)){
        printf("Stack is Empty!");
        return INT_MIN;
    }
    Node* temp = stack->top;
    int data = temp->val;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
    return data;
}

int peek(Stack* stack){
    if(isEmpty(stack)){
        printf("Stack Underflow!");
        return INT_MIN;
    }
    return stack->top->val;
}

int size(Stack* stack){
    return stack->size;
}



void freeStack(Stack* stack){
    Node* current = stack->top;
    while(current){
        Node* temp = current;
        current = current -> next;
        free(temp);
    }
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
    
    printf("Is stack empty? %s\n", isEmpty(&st) ? "Yes" : "No");

    freeStack(&st);
    return 0;
}