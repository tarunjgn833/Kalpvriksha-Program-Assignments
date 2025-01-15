#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 50
 // this function does not handle whitespaces
int customAtoi(char *string)
{
    int num = 0;
    int sign = 1;
    char *str = string;

    if (*str == '-')
    {
        sign = -1;
        str++;
    }

    while (*str != '\0')
    {
        if (*str < '0' || *str > '9')
            return 0;
        num = (num * 10) + (*str - '0');
        str++;
    }

    return num * sign;
}

int main()
{
    char input[MAX_INPUT_LEN];
    scanf("%s",input);
    
    printf("%d", customAtoi(input));

    return 0;
}