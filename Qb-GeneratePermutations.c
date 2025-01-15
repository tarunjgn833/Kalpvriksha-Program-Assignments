#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN 100
void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

void generatePermutations(char *string, int l, int r)
{
    if (l == r)
    {
        printf("%s\n", string);
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            swap((string + l), (string + i));
            generatePermutations(string, l + 1, r);
            swap((string + l), (string + i));
        }
    }
}

int main()
{
    char string[MAX_INPUT_LEN];

    printf("Enter a string: ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")] = '\0';

    int n = strlen(string);
    generatePermutations(string, 0, n - 1);

    return 0;
}
