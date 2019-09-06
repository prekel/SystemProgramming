#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "Matrix.h"
#include "Input.h"

//#define MAX_STRING_LENGTH 100

bool MatrixSizeChecker(int n)
{
    return n >= 1;
}

bool MatrixElementChecker(int n)
{
    return true;
}

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main(int argc, char** argv)
{
    int rows = 0;
    int columns = 0;
    //printf("Введите порядок матриц: ");
    //fflush(stdout);
    //scanf("%d", &rows);
    columns = rows = CycleInputInt("Введите порядок матриц: ",
            MatrixSizeChecker);

    Matrix* matrix1 = CreateEmptyMatrix(rows, columns);
    Matrix* matrix2 = CreateEmptyMatrix(rows, columns);

    printf("Введите матрицу matrix1:\n");
    fflush(stdout);
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            //printf("matrix1[%d][%d] = ", i, j);
            //fflush(stdout);
            //scanf("%d", &matrix1->pData[i][j]);

            ssize_t len = snprintf(NULL, 0, "matrix1[%d][%d] = ", i, j);
            char* s = malloc(len + 1);
            snprintf(s, len + 1, "matrix1[%d][%d] = ", i, j);

            matrix1->pData[i][j] = CycleInputInt(s, MatrixElementChecker);
            
            free(s);
        }
    }
    printf("\n");
    fflush(stdout);

    printf("Введите матрицу matrix2:\n");
    fflush(stdout);
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            //printf("matrix2[%d][%d] = ", i, j);
            //fflush(stdout);
            //scanf("%d", &matrix2->pData[i][j]);

            ssize_t len = snprintf(NULL, 0, "matrix2[%d][%d] = ", i, j);
            char* s = malloc(len + 1);
            snprintf(s, len + 1, "matrix2[%d][%d] = ", i, j);

            //sprintf(s, "matrix2[%d][%d] = ", i, j);
            matrix2->pData[i][j] = CycleInputInt(s, MatrixElementChecker);
            
            free(s);
        }
    }
    printf("\n");
    fflush(stdout);

    Matrix* sum = SumMatrices(matrix1, matrix2);

    printf("Матрица matrix1:\n");
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            printf("%d ", matrix1->pData[i][j]);
            fflush(stdout);
        }
        printf("\n");
    }
    printf("\n");
    fflush(stdout);

    printf("Матрица matrix2:\n");
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            printf("%d ", matrix2->pData[i][j]);
            fflush(stdout);
        }
        printf("\n");
    }
    printf("\n");
    fflush(stdout);

    printf("Сумма матриц matrix1 + matrix2:\n");
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            printf("%d ", sum->pData[i][j]);
            fflush(stdout);
        }
        printf("\n");
    }
    printf("\n");
    fflush(stdout);

    int det = CalculateDeterminant(sum);
    printf("Определитель суммы матриц det = %d\n", det);
    fflush(stdout);

    FreeMatrix(matrix1);
    FreeMatrix(matrix2);
    FreeMatrix(sum);

	return 0;
}
