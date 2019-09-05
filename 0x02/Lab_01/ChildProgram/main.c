#include <stdio.h>

#include "Matrix.h"

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main()
{
    int rows = 2;
    int columns = 3;
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

    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            printf("matrix2[%d][%d] = ", i, j);
            fflush(stdout);
            scanf("%d", &matrix2->pData[i][j]);
        }
    }

    struct Matrix* sum = SumMatrices(matrix1, matrix2);

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

    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            printf("%d ", sum->pData[i][j]);
            fflush(stdout);
        }
        printf("\n");
    }

    FreeMatrix(matrix1);
    FreeMatrix(matrix2);
    FreeMatrix(sum);

	return 0;
}
