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
    assert(pRet);
    pRet->SecondCount = secondCount;
    pRet->FirstCount = firstCount;
    pRet->pData = (int**) malloc(pRet->FirstCount * sizeof(int*));
    assert(pRet->pData);

    for (int i = 0; i < pRet->FirstCount; i++)
    {
//        pRet->pData[i] = (int*) malloc(pRet->SecondCount * sizeof(int));
//        RETURN_NULL_IF_NULLPTR(pRet->pData[i]);
//        for (int j = 0; j < pRet->SecondCount; j++)
//        {
//            pRet->pData[i][j] = 0;
//        }
        pRet->pData[i] = (int*) calloc(pRet->SecondCount, sizeof(int));
        assert(pRet->pData[i]);
    }

    return pRet;
}

Matrix* CreateEmptyMatrix(int firstCount, int secondCount)
{
    Matrix* pRet = (Matrix*) malloc(sizeof(Matrix));
    assert(pRet);
    pRet->SecondCount = secondCount;
    pRet->FirstCount = firstCount;
    pRet->pData = (int**) malloc(pRet->FirstCount * sizeof(int*));
    assert(pRet->pData);

    for (int i = 0; i < pRet->FirstCount; i++)
    {
        pRet->pData[i] = (int*) malloc(pRet->SecondCount * sizeof(int));
        assert(pRet->pData[i]);
    }
    return pRet;
}

Matrix* SumMatrices(Matrix* pMatrixResult, Matrix* pMatrixA, Matrix* pMatrixB)
{
    assert(pMatrixA->SecondCount == pMatrixB->SecondCount);
    assert(pMatrixA->FirstCount == pMatrixB->FirstCount);

    for (int i = 0; i < pMatrixResult->FirstCount; i++)
    {
        for (int j = 0; j < pMatrixResult->SecondCount; j++)
        {
            pMatrixResult->pData[i][j] =
                    pMatrixA->pData[i][j] + pMatrixB->pData[i][j];
        }
    }

    return pMatrixResult;
}

Matrix* GetMinor(Matrix* pMinorResult, Matrix* pMatrix, int firstIndex,
                 int secondIndex)
{
    Matrix* pRet;
    if (pMinorResult == NULL)
    {
        pRet = CreateEmptyMatrix(
                pMatrix->FirstCount - 1,
                pMatrix->SecondCount - 1);
        assert(pRet);
    }
    else
    {
        pRet = pMinorResult;
    }

    for (int i = 0; i < pRet->FirstCount; i++)
    {
        for (int j = 0; j < pRet->SecondCount; j++)
        {
            int oldI = i;
            int oldJ = j;
            if (i >= firstIndex)
            {
                oldI++;
            }
            if (j >= secondIndex)
            {
                oldJ++;
            }
            pRet->pData[i][j] = pMatrix->pData[oldI][oldJ];
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
    assert(pMatrix->FirstCount >= 1);

    int n = pMatrix->FirstCount;

    if (n == 1)
    {
        return pMatrix->pData[0][0];
    }
    else if (n == 2)
    {
        return CalculateDeterminant2x2(pMatrix);
    }
    else
    {
        int ret = 0;
        Matrix* pMinor = CreateEmptyMatrix(
                pMatrix->FirstCount - 1,
                pMatrix->SecondCount - 1);
        assert(pMinor);
        for (int i = 0; i < pMatrix->FirstCount; i++)
        {
            int sign = (i % 2) ? -1 : 1;
            pMinor = GetMinor(pMinor, pMatrix, 0, i);
            int det = CalculateDeterminant(pMinor);
            int firstRow = pMatrix->pData[0][i];
            ret += sign * firstRow * det;
        }
        DestroyMatrix(pMinor);
        return ret;
    }
}

void DestroyMatrix(Matrix* pMatrix)
{
    if (pMatrix == NULL)
    {
        return;
    }
    for (int i = 0; i < pMatrix->FirstCount; i++)
    {
        free(pMatrix->pData[i]);
    }
    free(pMatrix->pData);
    free(pMatrix);
}
