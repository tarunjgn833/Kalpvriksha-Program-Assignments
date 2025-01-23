#include <stdio.h>

#define MAX_INPUT_LEN 1000

int Strcspn(char *input, char delim)
{
    int len = 0;
    while (*input != '\0')
    {
        if (*input == delim)
            return len;
        len++;
        input++;
    }
    return len;
}

int getLength(char* input)
{
    return Strcspn(input,'\0');
}

void printReverse(char* input)
{
    int len = getLength(input);
    printf("Reversed String: ");

    for (int i = len - 1; i >= 0; i--)
    {
        printf("%c", input[i]);
    }
    printf("\n");
}

void printUpperCase(char* input)
{
    printf("Uppercase String: ");
    while (*input != '\0')
    {
        if (*input >= 'a' && *input <= 'z')
        {
            printf("%c", *input - 'a' + 'A');
        }
        else
        {
            printf("%c", *input);
        }
        input++;
    }
    printf("\n");
}

void ifPalindrome(char* input)
{
    int len = getLength(input);

    int isPalindrome = 1;
    for (int i = 0; i < len / 2; i++)
    {
        if (input[i] != input[len - i - 1])
        {
            isPalindrome = 0;
            break;
        }
    }

    if (isPalindrome)
        printf("The string is a palindrome.\n");
    else
        printf("The string is not a palindrome.\n");
}

int main()
{
    char input[MAX_INPUT_LEN];
    int option, validInput;
    do
    {
        printf("1. Find Length of String\n");
        printf("2. Reverse String\n");
        printf("3. String to UpperCase\n");
        printf("4. Check If Palindrome\n");
        printf("5. Exit\n");

        printf("\nEnter Option: ");
        validInput = scanf("%d", &option);
        getchar(); // to consume newline

        if (validInput != 1)
        {
            printf("Invalid input! Please enter an integer.\n\n");
            while (getchar() != '\n');
            continue;
        }

        if (option >= 1 && option <= 4)
        {
            printf("Enter a String: ");
            if (fgets(input, sizeof(input), stdin) == NULL)
            {
                printf("Error Reading Input!!\n");
                return 1;
            }
            input[Strcspn(input, '\n')] = '\0'; // Remove newline
        }

        switch (option)
        {
        case 1:
            int len = getLength(input);
            printf("String Length: %d\n", len);
            break;
        case 2:
            printReverse(input);
            break;
        case 3:
            printUpperCase(input);
            break;
        case 4:
            ifPalindrome(input);
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid Choice! Please try again..\n");
            break;
        }
        printf("\n\n");
    } while (option != 5);

    return 0;
}
