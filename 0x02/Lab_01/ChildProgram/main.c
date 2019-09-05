#include <stdio.h>

#include "Matrix.h"

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main()
{
    int rows = 4;
    int columns = 4;
    struct Matrix* matrix1 = CreateEmptyMatrix(rows, columns);
    struct Matrix* matrix2 = CreateEmptyMatrix(rows, columns);

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

    struct Matrix* sum = SumMatrices(matrix1, matrix2);

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
    printf("Определитель суммы матриц det = %d", det);
    fflush(stdout);

    FreeMatrix(matrix1);
    FreeMatrix(matrix2);
    FreeMatrix(sum);

	return 0;
}
