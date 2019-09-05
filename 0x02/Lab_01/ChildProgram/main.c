#include <stdio.h>

#include "Matrix.h"

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main()
{
    int rows = 0;
    int columns = 0;
    printf("Введите порядок матриц: ");
    fflush(stdout);
    scanf("%d", &rows);
    columns = rows;

    Matrix* matrix1 = CreateEmptyMatrix(rows, columns);
    Matrix* matrix2 = CreateEmptyMatrix(rows, columns);

    printf("Введите матрицу matrix1:\n");
    fflush(stdout);
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            printf("matrix1[%d][%d] = ", i, j);
            fflush(stdout);
            scanf("%d", &matrix1->pData[i][j]);
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
            printf("matrix2[%d][%d] = ", i, j);
            fflush(stdout);
            scanf("%d", &matrix2->pData[i][j]);
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
