/// \file
/// \brief Реализация функций из Matrix.h
/// \details Реализация функций из Matrix.h.

#include <malloc.h>
#include <assert.h>
#include <stddef.h>

#include "Matrix.h"

Matrix* CreateBlankMatrix(int firstCount, int secondCount)
{
    assert(firstCount > 0);
    assert(secondCount > 0);
    Matrix* pRet = (Matrix*) malloc(sizeof(Matrix));
    assert(pRet);
    pRet->SecondCount = secondCount;
    pRet->FirstCount = firstCount;
    pRet->ppData = (int**) malloc(pRet->FirstCount * sizeof(int*));
    assert(pRet->ppData);

    for (int i = 0; i < pRet->FirstCount; i++)
    {
        pRet->ppData[i] = (int*) calloc(pRet->SecondCount, sizeof(int));
        assert(pRet->ppData[i]);
    }

    return pRet;
}

Matrix* CreateEmptyMatrix(int firstCount, int secondCount)
{
    assert(firstCount > 0);
    assert(secondCount > 0);
    Matrix* pRet = (Matrix*) malloc(sizeof(Matrix));
    assert(pRet);
    pRet->SecondCount = secondCount;
    pRet->FirstCount = firstCount;
    pRet->ppData = (int**) malloc(pRet->FirstCount * sizeof(int*));
    assert(pRet->ppData);

    for (int i = 0; i < pRet->FirstCount; i++)
    {
        pRet->ppData[i] = (int*) malloc(pRet->SecondCount * sizeof(int));
        assert(pRet->ppData[i]);
    }
    return pRet;
}

void PrintMatrix(Matrix* pMatrix)
{
    for (int i = 0; i < pMatrix->FirstCount; i++)
    {
        for (int j = 0; j < pMatrix->SecondCount; j++)
        {
            printf("%d ", pMatrix->ppData[i][j]);
        }
        printf("\n");
    }
}

Matrix* SumMatrices(Matrix* pSumResult, Matrix* pMatrixA, Matrix* pMatrixB)
{
    assert(pMatrixA->FirstCount == pMatrixB->FirstCount);
    assert(pMatrixA->SecondCount == pMatrixB->SecondCount);

    Matrix* pSum;
    if (pSumResult)
    {
        pSum = pSumResult;
    }
    else
    {
        pSum = CreateEmptyMatrix(pMatrixA->FirstCount, pMatrixA->SecondCount);
    }

    for (int i = 0; i < pMatrixA->FirstCount; i++)
    {
        for (int j = 0; j < pMatrixA->SecondCount; j++)
        {
            pSum->ppData[i][j] =
                    pMatrixA->ppData[i][j] + pMatrixB->ppData[i][j];
        }
    }
    return pSum;
}

Matrix* GetMinor(Matrix* pMinorResult, Matrix* pMatrix, int firstIndex,
                 int secondIndex)
{
    assert(pMatrix);
    assert(0 <= firstIndex && firstIndex < pMatrix->FirstCount);
    assert(0 <= secondIndex && secondIndex < pMatrix->SecondCount);

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
        assert(pMinorResult->FirstCount == pMatrix->FirstCount - 1);
        assert(pMinorResult->SecondCount == pMatrix->SecondCount - 1);
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
            pRet->ppData[i][j] = pMatrix->ppData[oldI][oldJ];
        }
    }

    return pRet;
}

int CalculateDeterminant2x2(Matrix* pMatrix)
{
    assert(pMatrix->FirstCount == 2);
    assert(pMatrix->SecondCount == 2);

    int a = pMatrix->ppData[0][0];
    int b = pMatrix->ppData[0][1];
    int c = pMatrix->ppData[1][0];
    int d = pMatrix->ppData[1][1];

    return a * d - c * b;
}

int CalculateDeterminant(Matrix* pMatrix)
{
    assert(pMatrix->FirstCount == pMatrix->SecondCount);
    assert(pMatrix->FirstCount >= 1);

    int n = pMatrix->FirstCount;

    if (n == 1)
    {
        return pMatrix->ppData[0][0];
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
            int firstRow = pMatrix->ppData[0][i];
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
        free(pMatrix->ppData[i]);
    }
    free(pMatrix->ppData);
    free(pMatrix);
}
