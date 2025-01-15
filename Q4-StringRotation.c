#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 100

void concatString(char *string1, char *string2, char *output)
{
    while (*string1 != '\0')
    {
        *output = *string1;
        output++;
        string1++;
    }
    while (*string2 != '\0')
    {
        *output = *string2;
        output++;
        string2++;
    }
    *output = '\0';
}

int checkSubString(char *string, char *substr)
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
            return 1;
        }
    }
    return 0;
}

int areRotations(char *string1, char *string2)
{
    int string1Len = strlen(string1);
    int string2Len = strlen(string2);

    if (string1Len != string2Len)
        return 0;

    char concatStr[1 + (string1Len * 2)];

    concatString(string1, string1, concatStr);

    return checkSubString(concatStr, string2);
}

int main()
{
    char input[MAX_INPUT_LEN];
    char substr[MAX_INPUT_LEN];

    printf("Enter First String: ");
    scanf("%s", input);
    printf("\nEnter Second String: ");
    scanf("%s", substr);

    printf("\nAre Rotations? : %s", areRotations(input, substr) ? "true" : "false");

    return 0;
}