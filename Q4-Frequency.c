#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rows, cols;

    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    int **matrix = (int **)malloc(rows * sizeof(int *));

    printf("Enter the elements of the matrix (numbers between 1 and 100):\n");
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++)
        {
            printf("Enter value at (%d, %d): ", i, j);
            scanf("%d", &matrix[i][j]);
            if (*(*(matrix + i) + j) < 1 || *(*(matrix + i) + j) > 100)
            {
                printf("Error: Number out of bounds at this position.\n");
                return 1;
            }
        }
    }

    int frequency[101] = {0};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            frequency[*(*(matrix + i) + j)]++;
        }
    }

    printf("Frequency of each number:\n");
    for (int i = 1; i <= 100; i++)
    {
        if (frequency[i] > 0)
        {
            printf("%d -> %d times\n", i, frequency[i]);
        }
    }

    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
