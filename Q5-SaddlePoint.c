#include <stdio.h>
#include <stdlib.h>

void printSaddlePoint(int rows, int cols, int **matrix)
{
    for (int i = 0; i < rows; i++)
    {
        int rowMin = matrix[i][0];
        int columnIndex = 0;

        for (int j = 1; j < cols; j++)
        {
            if (matrix[i][j] < rowMin)
            {
                rowMin = matrix[i][j];
                columnIndex = j;
            }
        }

        int isSaddlePoint = 1;
        for (int k = 0; k < rows; k++)
        {
            if (matrix[k][columnIndex] > rowMin)
            {
                isSaddlePoint = 0;
                break;
            }
        }

        if (isSaddlePoint)
        {
            printf("%d", rowMin);
            return;
        }
    }

    printf("-1");
}

int main()
{
    int rows, cols;

    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    int **matrix = (int **)malloc(rows * sizeof(int *));

    printf("Enter the elements of the matrix:\n");

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++)
        {
            printf("Enter value at (%d, %d): ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    printSaddlePoint(rows, cols, matrix);

    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
