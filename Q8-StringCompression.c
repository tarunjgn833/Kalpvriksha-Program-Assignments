#include <stdio.h>
#include <string.h>

void compressString(char *input, char *output)
{
    int len = strlen(input);
    int count = 1;
    int j = 0;

    for (int i = 0; i < len; i++)
    {
        if (input[i] == input[i + 1])
        {
            count++;
        }
        else
        {
            output[j++] = input[i];
            if (count > 1)
            {
                output[j++] = count + '0';
            }
            count = 1;
        }
    }
    output[j] = '\0';
}

int main()
{
    char input[1000];
    char compressed[1000];

    printf("Enter Input String: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    compressString(input, compressed);

    if (strlen(compressed) < strlen(input))
    {
        printf("Compressed String: %s\n", compressed);
    }
    else
    {
        printf("Original String: %s\n", input);
    }

    return 0;
}
