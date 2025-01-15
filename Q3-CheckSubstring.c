#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 1000

int getSubString(char *string, char *substr)
{
    int stringLen = strlen(string);
    int substrLen = strlen(substr);

    if (substrLen > stringLen)
    {
        printf("Substring should be smaller than main string.\n");
        exit(1);
    }

    for (int i = 0; i <= stringLen - substrLen; i++)
    {
        int j = 0;
        for (; j < substrLen; j++)
        {
            if (string[i + j] != substr[j])
                break;
        }
        if (j == substrLen)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    char input[MAX_INPUT_LEN];
    char substr[MAX_INPUT_LEN];

    scanf("%s", input);
    scanf("%s", substr);

    printf("%d", getSubString(input, substr));

    return 0;
}