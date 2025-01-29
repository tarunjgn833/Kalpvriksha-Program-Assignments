#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Pair {
    int first;
    int second;
    int difference;
    struct Pair* next;
} Pair;

typedef struct Category {
    char* name;
    int startRange;
    int endRange;
    Pair* pairs;
    struct Category* next;
} Category;

// create Functions
Node* createLinkedList(int arr[], int size) {
    if (size == 0) return NULL;
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = arr[0];
    head->next = NULL;
    Node* current = head;
    
    for (int i = 1; i < size; i++) {
        current->next = (Node*)malloc(sizeof(Node));
        current = current->next;
        current->data = arr[i];
        current->next = NULL;
    }
    return head;
}

Pair* createPair(int first, int second, int diff) {
    Pair* newPair = (Pair*)malloc(sizeof(Pair));
    newPair->first = first;
    newPair->second = second;
    newPair->difference = diff;
    newPair->next = NULL;
    return newPair;
}

Category* createCategory(const char* name, int start, int end) {
    Category* cat = (Category*)malloc(sizeof(Category));
    cat->name = strdup(name);
    cat->startRange = start;
    cat->endRange = end;
    cat->pairs = NULL;
    cat->next = NULL;
    return cat;
}

// other utility functions
int stoi(const char* str) {
    if (str == NULL) {
        return 0;
    }

    int result = 0;
    int sign = 1;

    while (*str == ' ') {
        str++;
    }

    if (*str == '-') {
        sign = -1;
        str++;
    }

    while (*str && *str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    return sign * result;
}

int Strcspn(char *input, char delim)
{
    int len = 0;
    while (*input != '\0')
    {
        if (*input == delim)
            return len;
        len++;
        input++;
    }
    return len;
}


// parse array functions

int getSize(char* input){
    int size = 0;

    char *duplicate = (char*)malloc(strlen(input) + 1);

    if (duplicate != NULL) {
        strcpy(duplicate, input);
    } else {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    char* token = strtok(duplicate, " ");
    while(token != NULL){
        size++;
        token = strtok(NULL," ");
    }
    free(duplicate);
    return size;
}
int* parseArray(char* input, int* size) {
    *size = getSize(input);
    if(*size<2)return NULL;
    int* array = (int*)malloc(*size * sizeof(int));
    if (array == NULL) {
        printf("Failed to allocate memory");
        exit(1);
    }

    char* token = strtok(input, " ");
    int ind = 0;
    while (token != NULL) {
        array[ind++] = stoi(token);
        token = strtok(NULL, " ");
    }

    return array;
}

char** parseStringArray(char* input, int* size) {
    *size = getSize(input);
    if (*size > 5){
        printf("\n More than 5 categories not possible\n");
        exit(1);
    }
    
    char** array = (char**)malloc(*size * sizeof(char*));
    if (array == NULL) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    char* token = strtok(input, " ");
    int ind = 0;
    while (token != NULL) {
        array[ind++] = token;
        token = strtok(NULL, " ");
    }
    
    return array;
}


// problem utility functions

int findMaxDifference(Node* head) {
    int maxDiff = 0;
    Node* current = head;
    
    while (current != NULL && current->next != NULL) {
        int diff = abs(current->next->data - current->data);
        if (diff > maxDiff) {
            maxDiff = diff;
        }
        current = current->next;
    }
    
    return maxDiff;
}

//searching 
Category* findCategory(Category* categories, int difference) {
    Category* current = categories;
    while (current != NULL) {
        if (difference >= current->startRange && difference <= current->endRange) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//merge sorting used to display differences in ascending order
Pair* mergeSortedPairs(Pair* a, Pair* b) {
    if (!a) return b;
    if (!b) return a;
    
    Pair* result = NULL;
    if (a->difference <= b->difference) {
        result = a;
        result->next = mergeSortedPairs(a->next, b);
    } else {
        result = b;
        result->next = mergeSortedPairs(a, b->next);
    }
    return result;
}

void splitPairs(Pair* source, Pair** front, Pair** back) {
    if (!source || !source->next) {
        *front = source;
        *back = NULL;
        return;
    }
    
    Pair* slow = source;
    Pair* fast = source->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

void mergeSortPairs(Pair** head) {
    if (!*head || !(*head)->next) return;
    Pair* a;
    Pair* b;
    splitPairs(*head, &a, &b);
    
    mergeSortPairs(&a);
    mergeSortPairs(&b);
    
    *head = mergeSortedPairs(a, b);
}

Category* groupDifferencesIntoCategories(Node* head, char** categoryNames, int categoriesSize) {
    int maxDiff = findMaxDifference(head);
    int rangeSize = maxDiff / categoriesSize;
    
    Category* categories = NULL;
    Category* lastCategory = NULL;
    
    for (int i = 0; i < categoriesSize; i++) {
        int start = i * rangeSize + 1;
        int end = (i == categoriesSize - 1) ? maxDiff : (i + 1) * rangeSize;
        
        Category* newCat = createCategory(categoryNames[i], start, end);
        
        if (categories == NULL) {
            categories = newCat;
        } else {
            lastCategory->next = newCat;
        }
        lastCategory = newCat;
    }
    
    Node* current = head;
    
    while (current != NULL && current->next != NULL) {
        int diff = abs(current->next->data - current->data);
        Category* cat = findCategory(categories, diff);
        
        if (cat != NULL) {
            Pair* newPair = createPair(current->data, current->next->data, diff);
            newPair->next = cat->pairs;
            cat->pairs = newPair;
        }
        
        current = current->next;
    }
    
    Category* currentCategory = categories;
    while(currentCategory!=NULL){
        mergeSortPairs(&currentCategory->pairs);
        currentCategory = currentCategory->next;
    }
    return categories;
}

void printResults(Category* categories) {
    Category* currentCat = categories;
    
    while (currentCat != NULL) {
        printf("\n%s pairs (range %d-%d):\n", 
               currentCat->name, 
               currentCat->startRange, 
               currentCat->endRange);
        
        Pair* currentPair = currentCat->pairs;
        if (currentPair == NULL) {
            printf("  No pairs in this category\n");
        }
        
        while (currentPair != NULL) {
            printf("  (%d,%d) # difference: %d\n", 
                   currentPair->first, 
                   currentPair->second, 
                   currentPair->difference);
            currentPair = currentPair->next;
        }
        
        currentCat = currentCat->next;
    }
}


int main(){
    printf("\n============ Linked List Problem =============\n\n");
    printf(" Enter list(space separated): ");
    char input[100000];
    char categoriesInput[1000];
    int size, categoriesSize;
    fgets(input,sizeof(input),stdin);
    input[Strcspn(input,'\n')] = '\0';

    printf("\n Enter categories(space separated): ");
    fgets(categoriesInput,sizeof(categoriesInput),stdin);
    categoriesInput[Strcspn(categoriesInput,'\n')] = '\0';

    int* arr = parseArray(input,&size);
    char** categories = parseStringArray(categoriesInput,&categoriesSize);

    Node* head = createLinkedList(arr,size);
    Category* results = groupDifferencesIntoCategories(head, categories, categoriesSize);
    
    printResults(results);
    

    return 0;
}