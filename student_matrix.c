#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 51  

int isVowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int countVowelNames(char ***names, int rows, int cols) {
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (names[i][j][0] != '\0' && isVowel(names[i][j][0])) {
                count++;
            }
        }
    }
    return count;
}

char* findLongestName(char ***names, int rows, int cols) {
    int maxLength = 0;
    static char longestName[MAX_NAME_LENGTH];
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int currentLength = strlen(names[i][j]);
            if (currentLength > maxLength) {
                maxLength = currentLength;
                strcpy(longestName, names[i][j]);
            }
        }
    }
    return longestName;
}

void freeMemory(char ***names, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            free(names[i][j]);
        }
        free(names[i]);
    }
    free(names);
}

int main() {
    int rows, cols;
    char ***names;

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &cols);

    names = (char ***)malloc(rows * sizeof(char **));
    for (int i = 0; i < rows; i++) {
        names[i] = (char **)malloc(cols * sizeof(char *));
        for (int j = 0; j < cols; j++) {
            names[i][j] = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
        }
    }

    while (getchar() != '\n');
    printf("Enter the names:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Name at (%d,%d): ", i, j);
            fgets(names[i][j], MAX_NAME_LENGTH, stdin);
            names[i][j][strcspn(names[i][j], "\n")] = 0;
        }
    }

    int maxLength = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int currentLength = strlen(names[i][j]);
            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
        }
    }

    printf("\nThe 2D array of names is:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%-*s ", maxLength+2, names[i][j]); 
        }
        printf("\n");
    }

    int vowelCount = countVowelNames(names, rows, cols);
    printf("\nNumber of names starting with a vowel: %d\n", vowelCount);

    char* longest = findLongestName(names, rows, cols);
    printf("The longest name: %s\n", longest);

    freeMemory(names, rows, cols);

    return 0;
}
