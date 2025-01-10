#include <stdio.h>
#include <stdlib.h>

void printMatrix(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void rotateMatrix(int **matrix, int rows, int cols)
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = i + 1; j < cols; j++)
        {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols / 2; j++)
        {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[i][cols - j - 1];
            matrix[i][cols - j - 1] = temp;
        }
    }
}

int main()
{
    int rows, cols;

    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    if (rows != cols)
    {
        printf("Error: rows and columns are not of the same size.");
        return 1;
    }
    int **matrix = (int **)malloc(rows * sizeof(int *));

    printf("Enter the elements of the matrix:\n");

    // int count = 1; //for testing

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++)
        {
            printf("Enter value at (%d, %d): ", i, j);
            scanf("%d", &matrix[i][j]);
            // matrix[i][j] = count++; //for testing
        }
    }
    printf("\nMatrix before rotation:\n");
    printMatrix(matrix, rows, cols);

    rotateMatrix(matrix, rows, cols);

    printf("\nMatrix after 90 degree clock-wise rotation:\n");
    printMatrix(matrix, rows, cols);

    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}