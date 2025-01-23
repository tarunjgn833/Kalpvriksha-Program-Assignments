#include <stdio.h>

void printPyramid(int rows)
{
    printf("\n");
    for (int i = 1; i <= rows; i++)
    {
        printf("\t");
        for (int j = 1; j <= rows - i; j++)
        {
            printf("   ");
        }
        for (int k = 1; k <= 2 * i - 1; k++)
        {
            printf(" * ");
        }
        printf("\n");
    }
}

void printDiamond(int rows)
{
    printf("\n");
    for (int i = 1; i <= rows; i++)
    {
        printf("\t");
        for (int j = 1; j <= rows - i; j++)
        {
            printf("   ");
        }
        for (int k = 1; k <= 2 * i - 1; k++)
        {
            printf(" * ");
        }
        printf("\n");
    }

    for (int i = rows - 1; i >= 1; i--)
    {
        printf("\t");
        for (int j = 1; j <= rows - i; j++)
        {
            printf("   ");
        }
        for (int k = 1; k <= 2 * i - 1; k++)
        {
            printf(" * ");
        }
        printf("\n");
    }
}

void printPascalsTriangle(int rows)
{
    printf("\n");
    for (int i = 0; i < rows; i++)
    {
        printf("\t");
        int value = 1;
        for (int j = 1; j <= rows - i; j++)
        {
            printf("  ");
        }
        for (int k = 0; k <= i; k++)
        {
            printf(" %d  ", value);
            value = value * (i - k) / (k + 1);
        }
        printf("\n");
    }
}

int main()
{
    int choice, rows;
    do
    {
        printf("\n ======== Menu ========\n\n");
        printf(" 1. Print Pyramid\n");
        printf(" 2. Print Diamond\n");
        printf(" 3. Print Pascal's Triangle\n");
        printf(" 4. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3)
        {
            printf("Enter the number of rows: ");
            scanf("%d", &rows);
        }

        switch (choice)
        {
        case 1:
            printPyramid(rows);
            break;
        case 2:
            printDiamond(rows);
            break;
        case 3:
            printPascalsTriangle(rows);
            break;
        case 4:
            printf("Exiting program. Goodbye!\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}