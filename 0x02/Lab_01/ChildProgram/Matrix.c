#include <malloc.h>
#include <assert.h>

#include "Matrix.h"

Matrix* CreateEmptyMatrix(int rowsCount, int columnsCount)
{
    Matrix* ret = (Matrix*) malloc(sizeof(Matrix));
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

Matrix* SumMatrices(Matrix* MatrixA, Matrix* MatrixB)
{
    assert(MatrixA->RowsCount == MatrixB->RowsCount);
    assert(MatrixA->ColumnsCount == MatrixB->ColumnsCount);

    Matrix* ret =
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

Matrix* GetMinor(Matrix* matrix, int row, int column)
{
    Matrix* ret
            = CreateEmptyMatrix(
                    matrix->RowsCount - 1,
                    matrix->ColumnsCount - 1);

    for (int i = 0; i < ret->ColumnsCount; i++)
    {
        for (int j = 0; j < ret->RowsCount; j++)
        {
            int oldi = i;
            int oldj = j;
            if (i >= row)
            {
                oldi++;
            }
            if (j >= column)
            {
                oldj++;
            }
            ret->pData[i][j] = matrix->pData[oldi][oldj];
        }
    }
    return ret;
}

int CalculateDeterminant(Matrix* matrix)
{
    assert(matrix->ColumnsCount == matrix->RowsCount);

    int n = matrix->ColumnsCount;

    if (n == 1)
    {
        return matrix->pData[0][0];
    }
    if (n == 2)
    {
        int a = matrix->pData[0][0];
        int b = matrix->pData[1][0];
        int c = matrix->pData[0][1];
        int d = matrix->pData[1][1];
        return a * d - c * b;
    }
    if (n >= 3)
    {
        int ret = 0;
        for (int i = 0; i < matrix->ColumnsCount; i++)
        {
            int sign = (i % 2) ? -1 : 1;
            Matrix* minor = GetMinor(matrix, 0, i);
            int det = CalculateDeterminant(minor);
            int i1 = matrix->pData[0][i];
            ret += sign * i1 * det;
            FreeMatrix(minor);
        }
        return ret;
    }
}

void FreeMatrix(Matrix* a)
{
    for (int i = 0; i < a->ColumnsCount; i++)
        free(a->pData[i]);
    free(a->pData);
    free(a);
}