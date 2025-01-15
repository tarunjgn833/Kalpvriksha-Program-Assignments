#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 1000

void longestWord(char *input, char *output)
{
    char current_word[1000];
    int max_len = 0;
    int current_len = 0;
    int i = 0, j = 0;

    while (input[i] != '\0')
    {
        if (input[i] != ' ')
        {
            current_word[j++] = input[i];
            current_len++;
        }
        else
        {
            if (current_len > max_len)
            {
                max_len = current_len;
                current_word[j] = '\0';
                strcpy(output, current_word);
            }
            j = 0;
            current_len = 0;
        }
        i++;
    }

    if (current_len > max_len)
    {
        current_word[j] = '\0';
        strcpy(output, current_word);
    }
}
int main()
{
    char input[MAX_INPUT_LEN];
    char output[MAX_INPUT_LEN];

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    longestWord(input, output);
    printf("%s", output);

    return 0;
}