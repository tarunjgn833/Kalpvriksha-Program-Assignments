#include <stdio.h>
#include <string.h>

void removeCharacter(char *input, char ch) {
    int i = 0, j = 0;
    while (input[i] != '\0') {
        if (input[i] != ch) {
            input[j++] = input[i];
        }
        i++;
    }
    input[j] = '\0';
}

int main() {
    char input[1000];
    char ch;

    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("Enter the character to remove: ");
    scanf("%c", &ch);

    removeCharacter(input, ch);

    printf("Modified string: %s\n", input);

    return 0;
}
