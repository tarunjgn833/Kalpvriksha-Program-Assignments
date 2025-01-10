#include <stdio.h>
#include <stdlib.h>

void searchTarget(int **matrix, int target, int i, int j, int rows)
{
    if (i >= rows || j < 0)
    {
        printf("Element %d not found in the matrix.\n", target);
        return;
    }

    if (matrix[i][j] == target)
    {
        printf("Element %d found in the matrix at %d row, %d column.", target, i + 1, j + 1);
        return;
    }
    else if (matrix[i][j] > target)
    {
        searchTarget(matrix, target, i, j - 1, rows);
    }
    else
    {
        searchTarget(matrix, target, i + 1, j, rows);
    }
}

int main()
{
    int rows, cols;
    int target;

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

    printf("\nEnter Target to Search: ");
    scanf("%d", &target);

    searchTarget(matrix, target, 0, cols - 1, rows);

    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}