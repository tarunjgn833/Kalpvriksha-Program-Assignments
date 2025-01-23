#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int row;
    int col;
    int **value;
} Matrix;

Matrix matrix1 = {0, 0, NULL};
Matrix matrix2 = {0, 0, NULL};

int scanInt(int *n, int skip)
{
    char buffer[10];
    if (skip != 0 && skip != 1)
        skip = 0;

    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        if (skip == 1 && buffer[0] == '\n')
        {
            *n = 0;
            return 1;
        }
        if (sscanf(buffer, "%d", n) == 1)
        {
            return 1;
        }
        else
        {
            printf("Invalid input! Please enter a valid integer.\n");
        }
    }

    return 0;
}

int maxDigits(Matrix matrix)
{
    int maxVal = 0;
    int sign = 1;
    for (int i = 0; i < matrix.row; i++)
    {
        for (int j = 0; j < matrix.col; j++)
        {
            int val = abs(matrix.value[i][j]);
            while (val > 0)
            {
                maxVal = (val > maxVal) ? val : maxVal;
                val /= 10;
            }
        }
    }
    int digits = (maxVal == 0) ? 1 : 0;
    while (maxVal > 0)
    {
        maxVal /= 10;
        digits++;
    }
    return digits;
}

void printMatrix(Matrix matrix)
{
    printf("\n");
    int width = maxDigits(matrix) + 2; // to print evely spaced matrix
    for (int i = 0; i < matrix.row; i++)
    {
        for (int j = 0; j < matrix.col; j++)
        {
            printf("%*d ", width, matrix.value[i][j]);
        }
        printf("\n");
    }
}

int max(int a, int b)
{
    return a >= b ? a : b;
}

void takeMatrixInput(Matrix *matrix)
{
    for (int i = 0; i < matrix->row; i++)
    {
        matrix->value[i] = (int *)malloc(matrix->col * sizeof(int));
        for (int j = 0; j < matrix->col; j++)
        {
            printf("\n Enter Value for Matrix(%d, %d): ", i, j);
            while (scanInt(&matrix->value[i][j], 0) != 1)
                ;
        }
    }
}

void freeMatrix(Matrix *matrix)
{
    if (matrix->value != NULL)
    {
        for (int i = 0; i < matrix->row; i++)
        {
            free(matrix->value[i]);
        }
        free(matrix->value);
        matrix->value = NULL;
    }
}

void inputMatrices()
{
    int row1 = matrix1.row, col1 = matrix1.col;
    int row2 = matrix2.row, col2 = matrix2.col;

    printf("\n ========= Input Matrices =========\n\n");
    printf(" Note: To skip entering a matrix, simply press Enter(or input 0) when prompted for the row or column value.\n");

    printf("\n Enter Number of rows for First Matrix: ");
    while (scanInt(&row1, 1) != 1)
        ;
    if (row1 > 0)
    {
        printf(" Enter Number of columns for First Matrix: ");
        while (scanInt(&col1, 1) != 1)
            ;
    }
    if (row1 > 0 && col1 > 0)
    {
        matrix1.row = row1;
        matrix1.col = col1;
    }

    if (row1 > 0 && col1 > 0)
    {
        freeMatrix(&matrix1);
        matrix1.value = (int **)malloc(matrix1.row * sizeof(int *));
        printf("\n === Enter Values for First Matrix === \n");
        takeMatrixInput(&matrix1);
    }

    printf("\n Enter Number of rows for Second Matrix: ");
    while (scanInt(&row2, 1) != 1)
        ;
    if (row2 > 0)
    {
        printf(" Enter Number of columns for Second Matrix: ");
        while (scanInt(&col2, 1) != 1)
            ;
    }

    if (row2 > 0 && col2 > 0)
    {
        matrix2.row = row2;
        matrix2.col = col2;
    }

    if (row2 > 0 && col2 > 0)
    {
        freeMatrix(&matrix2);
        matrix2.value = (int **)malloc(matrix2.row * sizeof(int *));
        printf("\n === Enter Values for Second Matrix === \n");
        takeMatrixInput(&matrix2);
    }
}

void addMatrices()
{
    int flag = 0;

    printf("\n ========= Matrix Addition =========\n\n");
    printf("\n First Matrix: ");
    if (matrix1.value)
    {
        printMatrix(matrix1);
    }
    else
    {
        printf("NULL\n");
    }

    printf("\n Second Matrix: ");
    if (matrix1.value)
    {
        printMatrix(matrix2);
    }
    else
    {
        printf("NULL\n");
    }

    if ((matrix1.row > 0 && matrix2.row > 0 && matrix1.col > 0 && matrix2.col > 0) && (matrix1.row == matrix2.row && matrix1.col == matrix2.col))
    {
        flag = 1;
    }

    if (!flag)
    {
        printf("\n Incompatible Dimensions. These matrices cannot be added.\n");
        return;
    }

    printf("\n Matrix1 + Matrix2 :");
    printf("\n");
    int width = max(maxDigits(matrix1), maxDigits(matrix2));
    for (int i = 0; i < matrix1.row; i++)
    {
        for (int j = 0; j < matrix1.col; j++)
        {
            printf(" %*d ", width, matrix1.value[i][j] + matrix2.value[i][j]);
        }
        printf("\n");
    }
}

void subtractMatrices()
{
    int flag = 0;

    printf("\n ========= Matrix Subtraction =========\n\n");
    printf("\n First Matrix: ");
    if (matrix1.value)
    {
        printMatrix(matrix1);
    }
    else
    {
        printf("NULL\n");
    }

    printf("\n Second Matrix: ");
    if (matrix1.value)
    {
        printMatrix(matrix2);
    }
    else
    {
        printf("NULL\n");
    }

    if ((matrix1.row > 0 && matrix2.row > 0 && matrix1.col > 0 && matrix2.col > 0) && (matrix1.row == matrix2.row && matrix1.col == matrix2.col))
    {
        flag = 1;
    }

    if (!flag)
    {
        printf("\n Incompatible Dimensions. These matrices cannot be subtracted.\n");
        return;
    }

    printf("\n Matrix1 - Matrix2 :");
    printf("\n");
    int width = max(maxDigits(matrix1), maxDigits(matrix2));
    for (int i = 0; i < matrix1.row; i++)
    {
        for (int j = 0; j < matrix1.col; j++)
        {
            printf(" %*d ", width, matrix1.value[i][j] - matrix2.value[i][j]);
        }
        printf("\n");
    }
}

void multiplyMatrices()
{
    int flag = 0;

    printf("\n ========= Matrix Multiplication =========\n\n");
    printf("\n First Matrix: ");
    if (matrix1.value)
    {
        printMatrix(matrix1);
    }
    else
    {
        printf("NULL\n");
    }

    printf("\n Second Matrix: ");
    if (matrix1.value)
    {
        printMatrix(matrix2);
    }
    else
    {
        printf("NULL\n");
    }

    if ((matrix1.row > 0 && matrix2.row > 0 && matrix1.col > 0 && matrix2.col > 0) && (matrix1.col == matrix2.row))
    {
        flag = 1;
    }

    if (!flag)
    {
        printf("\n Incompatible Dimensions. These matrices cannot be subtracted.\n");
        return;
    }

    printf("\n Matrix1 * Matrix2: \n");
    for (int i = 0; i < matrix1.row; i++)
    {
        for (int j = 0; j < matrix2.col; j++)
        {
            int result = 0;

            for (int k = 0; k < matrix2.row; k++)
            {
                result += matrix1.value[i][k] * matrix2.value[k][j];
            }

            printf(" %d\t", result);
        }

        printf("\n");
    }
}

void printTranspose(Matrix matrix)
{
    printf("\n");
    int width = maxDigits(matrix);
    for (int i = 0; i < matrix.row; i++)
    {
        for (int j = 0; j < matrix.col; j++)
        {
            printf(" %*d ", width, matrix.value[j][i]);
        }
        printf("\n");
    }
}
void transposeMatrix()
{
    printf("\n ========= Matrix Transpose =========\n\n");
    printf("\n First Matrix: ");
    if (matrix1.value)
    {
        printMatrix(matrix1);
        printf("\n Transpose:\n");
        printTranspose(matrix1);
    }
    else
    {
        printf("NULL\n");
    }

    printf("\n Second Matrix: ");
    if (matrix1.value)
    {
        printMatrix(matrix2);
        printf("\n Transpose:\n");
        printTranspose(matrix2);
    }
    else
    {
        printf("NULL\n");
    }
}

void freeAll()
{
    freeMatrix(&matrix1);
    freeMatrix(&matrix2);
}

int main()
{
    int option;
    do
    {
        printf("\n ========= Matrix Operations =========\n\n");
        printf(" 1. Enter Matrices\n");
        printf(" 2. Add Matrices\n");
        printf(" 3. Subtract Matrices\n");
        printf(" 4. Multiply Matrices\n");
        printf(" 5. Transpose Matrix\n");
        printf(" 6. Exit\n");

        printf("\nEnter Option: ");
        if (scanInt(&option, 0) != 1)
            continue;

        switch (option)
        {
        case 1:
            inputMatrices();
            break;
        case 2:
            addMatrices();
            break;
        case 3:
            subtractMatrices();
            break;
        case 4:
            multiplyMatrices();
            break;
        case 5:
            transposeMatrix();
            break;
        case 6:
            freeAll();
            printf("Exit\n");
            break;
        default:
            printf("Invalid Choice! Please try again..\n");
            break;
        }
        printf("\n\n");
    } while (option != 6);

    return 0;
}