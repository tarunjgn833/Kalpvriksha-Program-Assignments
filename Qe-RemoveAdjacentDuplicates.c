#include <stdio.h>
#include <string.h>
#define MAX_INPUT_LEN 100

void removeAdjacentDuplicates(char *string)
{
    int len = strlen(string);

    if (len <= 1)
        return;

    int j = 0;

    for (int i = 0; i < len; i++)
    {
        int repeated = 0;

        while (i + 1 < len && string[i] == string[i + 1])
        {
            repeated = 1;
            i++;
        }

        if (!repeated)
        {
            string[j++] = string[i];
        }
    }
    string[j] = '\0';

    if (j < len)
    {
        removeAdjacentDuplicates(string);
    }
}

int main()
{
    char string[MAX_INPUT_LEN];

    printf("Enter String: ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")] = '\0';

    removeAdjacentDuplicates(string);

    printf("Modified String: %s\n", string);

    return 0;
}
