#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "MatrixIO.h"

void ReadMN(int* pM, int* pN)
{
    printf("Введите M и N (кол-во строк и столбцов, a[M][N]): ");
    scanf("%d%d", pM, pN);
}

void ReadMatrix(int* pMatrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Введите a[%d][%d]: ", i, j);
            scanf("%d", &pMatrix[i * n + j]);
        }
    }
}

void WriteMatrix(int* pMatrix, int m, int n)
{
    printf("Матрица a[%d][%d]:\n", m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", pMatrix[i * n + j]);
        }
        printf("\n");
    }
}
