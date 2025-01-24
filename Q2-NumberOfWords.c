#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN 1000

int countWords(char *string)
{
    int lastWasWord = 0;
    int wordCount = 0;

    for (int i = 0; string[i] != '\0'; i++)
    {

        if (string[i] != ' ')
        {
            if (!lastWasWord)
                wordCount++;
            lastWasWord = 1;
        }
        else
        {
            lastWasWord = 0;
        }
    }
    return wordCount;
}

int main()
{
    char input[MAX_INPUT_LEN];

    fgets(input, sizeof(input), stdin);
    printf("Enter String: ");
    input[strcspn(input, "\n")] = '\0';

    printf("\n Number of Words: %d", countWords(input));
    return 0;
}