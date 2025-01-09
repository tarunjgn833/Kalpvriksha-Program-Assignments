#include <stdio.h>
#include <stdlib.h>

void printDiagonalSum(int rows, int cols, int **array){
    int diagonalSum = 0;

    for(int i = 0; i < rows; i++){
        diagonalSum += array[i][i]; 
        if (i != cols - i - 1) {
            diagonalSum += array[i][cols - i - 1];
        }
    }

    printf("Diagonal Sum: %d\n", diagonalSum);
}

int main(){
    int rows, cols;
    int diagonalSum;

    printf("Enter Rows: ");
    scanf("%d",&rows);
    printf("Enter Columns: ");
    scanf("%d",&cols);

    int **array = (int**)malloc(rows * sizeof(int*));

    printf("Enter Values: ");

    for(int i=0;i<rows;i++){
        array[i] = (int*)malloc(cols * sizeof(int));
        for(int j=0;j<cols;j++){
            printf("Enter element at [%d][%d]: ", i, j);
            scanf("%d", &array[i][j]);
        }
    }

    printDiagonalSum(rows, cols, array);

    for(int i = 0; i < rows; i++){
        free(array[i]);
    }
    free(array);

    return 0;

}