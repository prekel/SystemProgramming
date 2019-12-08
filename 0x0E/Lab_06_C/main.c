#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    int M;
    int N;
    int** pData;
} Matrix;

bool IsOnly(Matrix* pMatrix, int k, bool isRow)
{
    for (int i = 0; i < pMatrix->M; i++)
    {
        for (int j = 0; j < pMatrix->N; j++)
        {
            if (pMatrix->pData[k][i] == pMatrix->pData[k][j])
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    return 0;
}
