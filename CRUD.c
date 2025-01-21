#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *head = NULL;
Node *tail = NULL;
int size = 0;

void insertAtBeginning(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->next = head;
    head = node;
    if (tail == NULL)
    {
        tail = node;
    }
    size++;
}

void insertAtEnd(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    if (head == NULL)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
    size++;
}

void insertAtPosition(int position, int value)
{
    if (position < 1 || position > size + 1)
    {
        printf("\n\nError: Invalid Position!\n");
        return;
    }
    if (position == 1)
    {
        insertAtBeginning(value);
        return;
    }
    if (position == size + 1)
    {
        insertAtEnd(value);
        return;
    }
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    Node *itr = head;
    for (int i = 1; i < position - 1; i++)
    {
        itr = itr->next;
    }
    node->next = itr->next;
    itr->next = node;
    size++;
}

void display()
{
    if (head == NULL)
    {
        printf("\nError: List is Empty!\n");
        return;
    }
    Node *current = head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void updateAtPosition(int position, int value)
{
    if (head == NULL)
    {
        printf("\nError: List is Empty!\n");
        return;
    }

    if (position < 1 || position > size)
    {
        printf("\nError: Invalid Position!\n");
        return;
    }
    Node *current = head;
    for (int i = 1; i < position; i++)
    {
        current = current->next;
    }
    current->data = value;
}

void deleteAtBeginning()
{
    if (head == NULL)
    {
        printf("\nError: List is Empty!\n");
        return;
    }
    Node *temp = head;
    head = head->next;
    if (head == NULL)
    {
        tail = NULL;
    }
    free(temp);
    size--;
}

void deleteAtEnd()
{
    if (head == NULL)
    {
        printf("\nError: List is Empty!\n");
        return;
    }
    if (head->next == NULL)
    {
        free(head);
        head = NULL;
        tail = NULL;
        size--;
        return;
    }
    Node *current = head;
    while (current->next != tail)
    {
        current = current->next;
    }
    free(tail);
    tail = current;
    tail->next = NULL;
    size--;
}

void deleteAtPosition(int position)
{
    if (head == NULL)
    {
        printf("\nError: List is Empty!\n");
        return;
    }
    if (position < 1 || position > size)
    {
        printf("\nError: Invalid Position!\n");
        return;
    }
    if (position == 1)
    {
        deleteAtBeginning();
        return;
    }
    if (position == size)
    {
        deleteAtEnd();
        return;
    }
    Node *current = head;
    for (int i = 1; i < position - 1; i++)
    {
        current = current->next;
    }
    Node *temp = current->next;
    current->next = temp->next;
    free(temp);
    size--;
}

int stoi(const char *str)
{
    if (str == NULL)
    {
        return 0;
    }

    int result = 0;
    int sign = 1;

    while (*str == ' ')
    {
        str++;
    }

    if (*str == '-')
    {
        sign = -1;
        str++;
    }

    while (*str && *str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }

    return sign * result;
}

void handleOperation()
{
    char input[100];
    char *token;
    int operation, value, position;

    while (1)
    {
        printf("Enter Operation: ");
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\nError: Failed to read input.\n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0'; // replaces newline with null termination character

        token = strtok(input, " ");
        if (token == NULL)
        {
            printf("\nError: No operation entered. Please try again.\n");
            continue;
        }

        operation = stoi(token);

        switch (operation)
        {
        case 1:
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                printf("\nError: Missing value for operation 1.\n");
                continue;
            }
            value = stoi(token);
            insertAtEnd(value);
            return;

        case 2:
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                printf("\nError: Missing value for operation 2.\n");
                continue;
            }
            value = stoi(token);
            insertAtBeginning(value);
            return;

        case 3:
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                printf("\nError: Missing position for operation 3.\n");
                continue;
            }
            position = stoi(token);

            token = strtok(NULL, " ");
            if (token == NULL)
            {
                printf("\nError: Missing value for operation 3.\n");
                continue;
            }
            value = stoi(token);

            insertAtPosition(position, value);
            return;

        case 4:
            display();
            return;

        case 5:
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                printf("\nError: Missing position for operation 5.\n");
                continue;
            }
            position = stoi(token);

            token = strtok(NULL, " ");
            if (token == NULL)
            {
                printf("\nError: Missing value for operation 5.\n");
                continue;
            }
            value = stoi(token);

            updateAtPosition(position, value);
            return;

        case 6:
            deleteAtBeginning();
            return;

        case 7:
            deleteAtEnd();
            return;

        case 8:
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                printf("\nError: Missing position for operation 8.\n");
                continue;
            }
            position = stoi(token);

            deleteAtPosition(position);
            return;

        default:
            printf("\nError: Invalid operation. Please try again.\n");
        }
    }
}

int main()
{
    int totalOperations;
    printf("Enter Number of Operations: ");
    scanf("%d", &totalOperations);
    getchar(); // to consume the new line character

    if (totalOperations < 1 || totalOperations > 100)
    {
        printf("\nError: Number of Operations should be within [1, 100]\n");
        return 1;
    }
    while (totalOperations-- > 0)
    {
        handleOperation();
    }
    return 0;
}