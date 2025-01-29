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


int binarySearch(int* arr, int size, int target){
    int left = 0, right = size-1;

    while(left<=right){
        int mid = left + (right-left)/2;
        if(arr[mid]==target)
            return mid+1;
        else if(arr[mid]>target)
            right = mid-1;
        else
            left = mid+1;
    }
    return -1;
}

int main(){
    printf("\n============ Binary Search =============\n\n");
    printf(" Enter sorted array(space separated): ");
    char input[100000];
    int size, target;
    fgets(input,sizeof(input),stdin);
    input[Strcspn(input,'\n')] = '\0';
    printf("\n Enter Number to Search: ");
    while(scanInt(&target,0)!=1);

    int* arr = parseArray(input,&size);
    int index = binarySearch(arr,size,target);

    if(index == -1){
        printf("\n Element not found!\n\n");
    }else{
        printf("\n Element found at position: %d\n\n",index);
    }
    return 0;
}