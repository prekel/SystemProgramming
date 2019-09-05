#include <malloc.h>

#include "Matrix.h"

struct Matrix CreateEmptyMatrix(int n, int m)
{
    struct Matrix ret;
    ret.RowCount = m;
    ret.ColumnsCount = n;
    ret.pData = (int**) malloc(ret.ColumnsCount * sizeof(int*));

    for (int i = 0; i < ret.ColumnsCount; i++)
    {
        ret.pData[i] = (int*) malloc(ret.RowCount * sizeof(int));
        for (int j = 0; j < ret.RowCount; j++)
        {
            ret.pData[i][j] = 0;
        }
    }
    return ret;
}

void FreeMatrix(struct Matrix* a)
{
    for (int i = 0; i < a->ColumnsCount; i++)
        free(a->pData[i]);
    free(a->pData);
}