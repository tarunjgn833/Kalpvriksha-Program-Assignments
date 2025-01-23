#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decimalToBinary(int n)
{
    char binary[32];
    int i = 0;
    while (n > 0)
    {
        binary[i] = '0' + (n % 2);
        n = n / 2;
        i++;
    }
    printf("Binary: ");
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%c", binary[j]);
    }
    printf("\n");
}

void decimalToOctal(int n)
{
    char octal[32];
    int i = 0;
    while (n > 0)
    {
        octal[i] = '0' + (n % 8);
        n = n / 8;
        i++;
    }
    printf("Octal: ");
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%c", octal[j]);
    }
    printf("\n");
}

void decimalToHexadecimal(int n)
{
    char hex[32];
    int i = 0;
    while (n > 0)
    {
        int remainder = n % 16;
        if (remainder < 10)
            hex[i] = '0' + remainder;
        else
        {
            printf("== %d\n", remainder);
            hex[i] = 'A' + (remainder - 10);
        }
        n = n / 16;
        i++;
    }
    printf("Hexadecimal: ");
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%c", hex[j]);
    }
    printf("\n");
}

void binaryToDecimal(char binary[])
{
    int decimal = 0;
    int length = strlen(binary);
    for (int i = 0; i < length; i++)
    {
        if (binary[i] == '1')
        {
            decimal += (1 << (length - i - 1));
        }
    }
    printf("Decimal: %d\n", decimal);
}

void octalToDecimal(char octal[])
{
    int decimal = 0;
    int length = strlen(octal);
    for (int i = 0; i < length; i++)
    {
        decimal += (octal[i] - '0') * (1 << (3 * (length - i - 1)));
    }
    printf("Decimal: %d\n", decimal);
}

void hexToDecimal(char hex[])
{
    int decimal = 0;
    int length = strlen(hex);
    for (int i = 0; i < length; i++)
    {
        if (hex[i] >= '0' && hex[i] <= '9')
        {
            decimal += (hex[i] - '0') * (1 << (4 * (length - i - 1)));
        }
        else if (hex[i] >= 'A' && hex[i] <= 'F')
        {
            decimal += (hex[i] - 'A' + 10) * (1 << (4 * (length - i - 1)));
        }
    }
    printf("Decimal: %d\n", decimal);
}

int main()
{
    int choice, decimal;
    char binary[32], octal[32], hex[32];

    do
    {
        printf("\nMenu:\n");
        printf("1. Decimal to Binary\n");
        printf("2. Decimal to Octal\n");
        printf("3. Decimal to Hexadecimal\n");
        printf("4. Binary to Decimal\n");
        printf("5. Octal to Decimal\n");
        printf("6. Hexadecimal to Decimal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter a decimal number: ");
            scanf("%d", &decimal);
            decimalToBinary(decimal);
            break;
        case 2:
            printf("Enter a decimal number: ");
            scanf("%d", &decimal);
            decimalToOctal(decimal);
            break;
        case 3:
            printf("Enter a decimal number: ");
            scanf("%d", &decimal);
            decimalToHexadecimal(decimal);
            break;
        case 4:
            printf("Enter a binary number: ");
            scanf("%s", binary);
            binaryToDecimal(binary);
            break;
        case 5:
            printf("Enter an octal number: ");
            scanf("%s", octal);
            octalToDecimal(octal);
            break;
        case 6:
            printf("Enter a hexadecimal number: ");
            scanf("%s", hex);
            hexToDecimal(hex);
            break;
        case 7:
            printf("Exiting program...\n");
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
