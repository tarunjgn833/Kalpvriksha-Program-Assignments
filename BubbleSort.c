#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void bubbleSort(int* arr, int size){
    int swapped = 0;
    for(int i=0;i<size-1;i++){
        swapped = 0;
        for(int j=0;j<size-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(&arr[j],&arr[j+1]);
                swapped = 1;
            }
        }
        if(swapped==0)break;
    }
}

void printArray(int* arr, int size){
    printf("\n Printed Arrray: \t");
    for(int i=0;i<size;i++)
        printf("%d ",arr[i]);
    printf("\n");
}


int main(){
    printf("\n============ Bubble Sort =============\n\n");
    printf("Enter array(space separated): ");
    char input[100000];
    int size;
    fgets(input,sizeof(input),stdin);
    input[Strcspn(input,'\n')] = '\0';

    int* arr = parseArray(input,&size);
    bubbleSort(arr,size);
    printArray(arr,size);
    return 0;
}