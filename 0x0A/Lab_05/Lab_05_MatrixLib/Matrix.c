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
    pRet->pData = (int**) malloc(pRet->FirstCount * sizeof(int*));
    assert(pRet->pData);

    for (int i = 0; i < pRet->FirstCount; i++)
    {
        pRet->pData[i] = (int*) calloc(pRet->SecondCount, sizeof(int));
        assert(pRet->pData[i]);
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
    pRet->pData = (int**) malloc(pRet->FirstCount * sizeof(int*));
    assert(pRet->pData);

    for (int i = 0; i < pRet->FirstCount; i++)
    {
        pRet->pData[i] = (int*) malloc(pRet->SecondCount * sizeof(int));
        assert(pRet->pData[i]);
    }
    return pRet;
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
