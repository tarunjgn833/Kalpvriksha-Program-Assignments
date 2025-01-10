#include <stdio.h>

#define ROWS 3
#define COLS 4

int main()
{
    int matrix[ROWS][COLS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}};

    printf("Index based acess:\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nPointer arithmetic based acess:\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }

    printf("\n1-D based access\n");
    int *ptr = (int *)matrix;
    for (int i = 0; i < ROWS * COLS; i++)
    {
        printf("%d ", ptr[i]);
        if (i % COLS == 3)
            printf("\n");
    }

    return 0;
}
