#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

// hash map functions
#define MAX_CAPACITY 50

typedef struct Node
{
    int key;
    int val;
    struct Node *next;
} Node;

typedef struct KeyNode
{
    int key;
    struct KeyNode *next;
} KeyNode;

typedef struct HashMap
{
    size_t capacity;
    int size;
    Node **arr;
    KeyNode *keysHead;
    KeyNode *keysTail;
} HashMap;

typedef struct HashMapIterator
{
    HashMap *map;
    KeyNode *currentKeyNode;
} HashMapIterator;

// prototype functions
int hash(int, int);
HashMap *createHashMap();
void insert(HashMap *, int, int);
int getValue(HashMap *, int);
void freeHashMap(HashMap *);
HashMapIterator *getMapIterator(HashMap *);
int hasNext(HashMapIterator *);
Node *next(HashMapIterator *);
int scanInt(int *, int);

int hash(int key, int capacity)
{
    return key % capacity;
}

HashMap *createHashMap()
{
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    if (!map)
        return NULL;
    map->size = 0;
    map->capacity = MAX_CAPACITY;
    map->arr = (Node **)calloc(map->capacity, sizeof(Node *));
    map->keysHead = NULL;
    map->keysTail = NULL;
    return map;
}

void insert(HashMap *map, int key, int val)
{
    if (!map)
        return;

    int index = hash(key, map->capacity);
    Node *current = map->arr[index];

    // if key exists
    while (current != NULL)
    {
        if (current->key == key)
        {
            current->val = val;
            return;
        }
        current = current->next;
    }

    // if key does not exist
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    node->key = key;
    node->val = val;
    node->next = map->arr[index];
    map->arr[index] = node;
    map->size++;

    // insert into key list
    KeyNode *keyNode = (KeyNode *)malloc(sizeof(KeyNode));
    if (!keyNode)
        return;
    keyNode->key = key;
    keyNode->next = NULL;

    if (map->keysHead == NULL)
    {
        map->keysHead = keyNode;
        map->keysTail = keyNode;
    }
    else
    {
        map->keysTail->next = keyNode;
        map->keysTail = keyNode;
    }
}

int getValue(HashMap *map, int key)
{
    if (!map)
        return INT_MIN;

    int index = hash(key, map->capacity);
    Node *current = map->arr[index];

    while (current != NULL)
    {
        if (current->key == key)
            return current->val;
        current = current->next;
    }
    return INT_MIN;
}

int removeKey(HashMap *map, int key)
{
    if (!map)
        return 1;

    int index = hash(key, map->capacity);
    Node *current = map->arr[index];
    Node *prev = NULL;

    while (current)
    {
        if (current->key == key)
        {
            if (prev)
                prev->next = current->next;
            else
                map->arr[index] = current->next;

            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }

    KeyNode *currentKey = map->keysHead;
    KeyNode *prevKey = NULL;

    while (currentKey)
    {
        if (currentKey->key == key)
        {
            if (prevKey)
                prevKey->next = currentKey->next;
            else
                map->keysHead = currentKey->next;

            free(currentKey);
            return 0;
        }
        prevKey = currentKey;
        currentKey = currentKey->next;
    }

    return 1;
}

void freeHashMap(HashMap *map)
{
    if (!map)
        return;
    for (size_t i = 0; i < map->capacity; i++)
    {
        Node *entry = map->arr[i];
        while (entry)
        {
            Node *temp = entry;
            entry = entry->next;
            free(temp);
        }
    }

    // free keys linked list
    KeyNode *keyNode = map->keysHead;
    while (keyNode)
    {
        KeyNode *temp = keyNode;
        keyNode = keyNode->next;
        free(temp);
    }
    free(map->arr);
    free(map);
}

HashMapIterator *getMapIterator(HashMap *map)
{
    HashMapIterator *iterator = (HashMapIterator *)malloc(sizeof(HashMapIterator));
    iterator->map = map;
    iterator->currentKeyNode = map->keysHead;
    return iterator;
}

int hasNext(HashMapIterator *iterator)
{
    return iterator && iterator->currentKeyNode != NULL;
}

Node *next(HashMapIterator *iterator)
{
    if (!hasNext(iterator))
        return NULL;

    int key = iterator->currentKeyNode->key;
    iterator->currentKeyNode = iterator->currentKeyNode->next;

    int index = hash(key, iterator->map->capacity);
    Node *current = iterator->map->arr[index];
    while (current && current->key != key)
    {
        current = current->next;
    }
    return current;
}

// utility methods
int scanInt(int *n, int skip)
{
    char buffer[10];
    if (skip != 0 || skip != 1)
        skip = 0;

    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        if (skip == 1 && buffer[0] == '\n')
        {
            return 1;
        }
        if (sscanf(buffer, "%d", n) == 1)
        {
            return 1;
        }
        else
        {
            printf("Invalid input! Please enter a valid integer.\n");
        }
    }

    return 0;
}

void put(HashMap *map)
{
    int key, val;
    printf(" Enter Key: ");
    while (scanInt(&key, 0) != 1)
        ;
    printf(" Enter Value: ");
    while (scanInt(&val, 0) != 1)
        ;
    insert(map, key, val);
}

void search(HashMap *map)
{
    int key;

    printf(" Enter Key: ");
    while (scanInt(&key, 0) != 1)
        ;
    int searchVal = getValue(map, key);
    if (searchVal == INT_MIN)
        printf(" Invalid Key!\n");
    else
        printf(" Value: %d\n", searchVal);
}

void display(HashMap *map)
{
    HashMapIterator *itr = getMapIterator(map);
    printf(" Hash Map(Key, Value): \t");
    while (hasNext(itr))
    {
        int key = itr->currentKeyNode->key;
        int val = getValue(map, key);
        printf(" (%d, %d)", key, val);
        next(itr);
        if (hasNext(itr))
            printf(", ");
    }
    printf("\n");
    free(itr);
}

void delete(HashMap *map)
{
    int key;
    printf(" Enter Key: ");
    while (scanInt(&key, 0) != 1)
        ;
    if (removeKey(map, key))
    {
        printf(" Invalid Key!\n");
    }
    else
    {
        printf(" Key %d deleted.\n", key);
    }
}

int main()
{
    int choice;
    HashMap *map = createHashMap();

    printf("\n =============== Hash Map ==================\n\n");
    printf(" 1. Insert\n");
    printf(" 2. Search\n");
    printf(" 3. Delete\n");
    printf(" 4. Display\n");
    printf(" 5. Exit\n");

    do
    {
        printf("\n Enter Choice: ");
        while (scanInt(&choice, 0) != 1)
            ;

        switch (choice)
        {
        case 1:
            put(map);
            break;

        case 2:
            search(map);
            break;

        case 3:
            delete (map);
            break;

        case 4:
            display(map);
            break;
        case 5:
            printf(" Exiting..\n");
            break;

        default:
            printf(" Invalid Choice!\n");
            break;
        }
    } while (choice != 5);
    
    freeHashMap(map);
    
    return 0;
}