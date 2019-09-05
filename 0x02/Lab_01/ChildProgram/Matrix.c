#include <malloc.h>
#include <assert.h>

#include "Matrix.h"

struct Matrix* CreateEmptyMatrix(int rowsCount, int columnsCount)
{
    struct Matrix* ret = (struct Matrix*) malloc(sizeof(int));
    ret->RowsCount = rowsCount;
    ret->ColumnsCount = columnsCount;
    ret->pData = (int**) malloc(ret->ColumnsCount * sizeof(int*));

    for (int i = 0; i < ret->ColumnsCount; i++)
    {
        ret->pData[i] = (int*) malloc(ret->RowsCount * sizeof(int));
        for (int j = 0; j < ret->RowsCount; j++)
        {
            ret->pData[i][j] = 0;
        }
    }
    return ret;
}

struct Matrix* SumMatrices(struct Matrix* MatrixA, struct Matrix* MatrixB)
{
    assert(MatrixA->RowsCount == MatrixB->RowsCount);
    assert(MatrixA->ColumnsCount == MatrixB->ColumnsCount);

    struct Matrix* ret =
            CreateEmptyMatrix(MatrixA->RowsCount, MatrixA->ColumnsCount);

    for (int i = 0; i < ret->ColumnsCount; i++)
    {
        for (int j = 0; j < ret->RowsCount; j++)
        {
            ret->pData[i][j] = MatrixA->pData[i][j] + MatrixB->pData[i][j];
        }
    }

    return ret;
}

void FreeMatrix(struct Matrix* a)
{
    for (int i = 0; i < a->ColumnsCount; i++)
        free(a->pData[i]);
    free(a->pData);
    free(a);
}