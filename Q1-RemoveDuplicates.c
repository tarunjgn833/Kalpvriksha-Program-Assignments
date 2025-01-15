#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN 100

char *removeDuplicates(char *string, char *output)
{
    int frequencyMap[256] = {0};

    int itr = 0;

    for (int i = 0; string[i] != '\0'; i++)
    {
        if (!frequencyMap[string[i]])
        {
            output[itr++] = string[i];
            frequencyMap[string[i]]++;
        }
    }
    return output;
}
int main()
{
    char input[MAX_INPUT_LEN];
    char output[MAX_INPUT_LEN];

    printf("Enter String: ");
    fgets(input, MAX_INPUT_LEN, stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("Output: %s", removeDuplicates(input, output));
    return 0;
}