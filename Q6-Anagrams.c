#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 50
// this function does not handle whitespaces
int areAnagrams(char *string1, char *string2)
{
    int string1Len = strlen(string1);
    int string2Len = strlen(string2);

    if (string1Len != string2Len)
        return 0;

    int string1Freq[256] = {0};
    int string2Freq[256] = {0}; // character frequency tables for both strings

    for (int i = 0; string1[i] != '\0'; i++)
        string1Freq[string1[i]]++;

    for (int i = 0; string2[i] != '\0'; i++)
        string2Freq[string2[i]]++;

    for (int i = 0; i < 256; i++)
    {
        if (string1Freq[i] != string2Freq[i])
            return 0;
    }

    return 1;
}

int main()
{
    char string1[MAX_INPUT_LEN];
    char string2[MAX_INPUT_LEN];
    printf("Enter First String: ");
    scanf("%s", string1);
    printf("\nEnter First String: ");
    scanf("%s", string2);

    printf("Are Anagrams? :\n%s", areAnagrams(string1, string2) ? "true" : "false");

    return 0;
}