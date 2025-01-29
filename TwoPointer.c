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


int* twoPointers(int* arr, int size, int target){
    int left = 0, right = size-1;
    int* result = (int*)malloc(2*sizeof(int));

    while(left<right){
        int sum = arr[left]+arr[right];
        if(sum==target){
            result[0] = arr[left];
            result[1] = arr[right];
            return result;
        }
        else if(sum>target)
            right--;
        else
            left++;
    }
    return NULL;
}

int main(){
    printf("\n============ Two Poitners =============\n\n");
    printf(" Enter sorted array(space separated): ");
    char input[100000];
    int size, target;
    fgets(input,sizeof(input),stdin);
    input[Strcspn(input,'\n')] = '\0';
    printf("\n Enter target sum: ");
    while(scanInt(&target,0)!=1);

    int* arr = parseArray(input,&size);
    int* result = twoPointers(arr,size,target);

    if(result == NULL){
        printf("\n No pairs found whose sum is %d!\n\n",target);
    }else{
        printf("\n Pairs whose sum is %d: [%d,%d]\n\n",target,result[0],result[1]);
    }
    free(result);
    return 0;
}