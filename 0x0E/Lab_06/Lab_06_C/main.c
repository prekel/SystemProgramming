#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Matrix.h"

void ReadMatrix(int* pMatrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &pMatrix[i * n + j]);
        }
    }
}

void ReadMN(int* pM, int* pN)
{
    scanf("%d", pM);
    scanf("%d", pN);
}

int main()
{
    int m;
    int n;

    ReadMN(&m, &n);

    int* pMatrix = malloc(m * n * sizeof(int));

    ReadMatrix(pMatrix, m, n);

    int countRow = CountRow(pMatrix, m, n);
    printf("%d\n", countRow);
    int countLine = CountLine(pMatrix, m, n);
    printf("%d\n", countLine);

    free(pMatrix);

    return 0;
}
