/*! \file
 *
 *  \brief Implements functions of Matrix.h
 */

#include <malloc.h>
#include <assert.h>

#include "Matrix.h"

Matrix* CreateBlankMatrix(int firstCount, int secondCount)
{
    Matrix* pRet = (Matrix*) malloc(sizeof(Matrix));
    pRet->SecondCount = secondCount;
    pRet->FirstCount = firstCount;
    pRet->pData = (int**) malloc(pRet->FirstCount * sizeof(int*));

    for (int i = 0; i < pRet->FirstCount; i++)
    {
        pRet->pData[i] = (int*) malloc(pRet->SecondCount * sizeof(int));
        for (int j = 0; j < pRet->SecondCount; j++)
        {
            pRet->pData[i][j] = 0;
        }
    }

    return pRet;
}

Matrix* CreateEmptyMatrix(int firstCount, int secondCount)
{
    Matrix* pRet = (Matrix*) malloc(sizeof(Matrix));
    pRet->SecondCount = secondCount;
    pRet->FirstCount = firstCount;
    pRet->pData = (int**) malloc(pRet->FirstCount * sizeof(int*));

    for (int i = 0; i < pRet->FirstCount; i++)
    {
        pRet->pData[i] = (int*) malloc(pRet->SecondCount * sizeof(int));
    }
    return pRet;
}

Matrix* SumMatrices(Matrix* pMatrixA, Matrix* pMatrixB)
{
    assert(pMatrixA->SecondCount == pMatrixB->SecondCount);
    assert(pMatrixA->FirstCount == pMatrixB->FirstCount);

    Matrix* pRet =
            CreateEmptyMatrix(pMatrixA->FirstCount, pMatrixA->SecondCount);

    for (int i = 0; i < pRet->FirstCount; i++)
    {
        for (int j = 0; j < pRet->SecondCount; j++)
        {
            pRet->pData[i][j] = pMatrixA->pData[i][j] + pMatrixB->pData[i][j];
        }
    }

    return pRet;
}

Matrix* GetMinor(Matrix* pMatrix, int firstIndex, int secondIndex)
{
    Matrix* pRet = CreateEmptyMatrix(
            pMatrix->FirstCount - 1,
            pMatrix->SecondCount - 1);

    for (int i = 0; i < pRet->FirstCount; i++)
    {
        for (int j = 0; j < pRet->SecondCount; j++)
        {
            int oldi = i;
            int oldj = j;
            if (i >= firstIndex)
            {
                oldi++;
            }
            if (j >= secondIndex)
            {
                oldj++;
            }
            pRet->pData[i][j] = pMatrix->pData[oldi][oldj];
        }
    }
    return pRet;
}

int CalculateDeterminant2x2(Matrix* pMatrix)
{
    assert(pMatrix->FirstCount == 2);
    assert(pMatrix->SecondCount == 2);

    int a = pMatrix->pData[0][0];
    int b = pMatrix->pData[0][1];
    int c = pMatrix->pData[1][0];
    int d = pMatrix->pData[1][1];
    return a * d - c * b;
}

int CalculateDeterminant(Matrix* pMatrix)
{
    assert(pMatrix->FirstCount == pMatrix->SecondCount);

    int n = pMatrix->FirstCount;

    if (n == 1)
    {
        return pMatrix->pData[0][0];
    }
    if (n == 2)
    {
        return CalculateDeterminant2x2(pMatrix);
    }
    if (n >= 3)
    {
        int ret = 0;
        for (int i = 0; i < pMatrix->FirstCount; i++)
        {
            int sign = (i % 2) ? -1 : 1;
            Matrix* minor = GetMinor(pMatrix, 0, i);
            int det = CalculateDeterminant(minor);
            int firstRow = pMatrix->pData[0][i];
            ret += sign * firstRow * det;
            FreeMatrix(minor);
        }
        return ret;
    }
}

void FreeMatrix(Matrix* pMatrix)
{
    for (int i = 0; i < pMatrix->FirstCount; i++)
    {
        free(pMatrix->pData[i]);
    }
    free(pMatrix->pData);
    free(pMatrix);
}