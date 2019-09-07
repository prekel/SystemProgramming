/*! \file ChildProgram/Matrix.c
 *
 *  \brief Implements functions of Matrix.h
 */

#include <malloc.h>
#include <assert.h>

#include "Matrix.h"

Matrix* CreateBlankMatrix(int firstCount, int secondCount)
{
    Matrix* ret = (Matrix*) malloc(sizeof(Matrix));
    ret->SecondCount = secondCount;
    ret->FirstCount = firstCount;
    ret->pData = (int**) malloc(ret->FirstCount * sizeof(int*));

    for (int i = 0; i < ret->FirstCount; i++)
    {
        ret->pData[i] = (int*) malloc(ret->SecondCount * sizeof(int));
        for (int j = 0; j < ret->SecondCount; j++)
        {
            ret->pData[i][j] = 0;
        }
    }

    return ret;
}

Matrix* CreateEmptyMatrix(int firstCount, int secondCount)
{
    Matrix* ret = (Matrix*) malloc(sizeof(Matrix));
    ret->SecondCount = secondCount;
    ret->FirstCount = firstCount;
    ret->pData = (int**) malloc(ret->FirstCount * sizeof(int*));

    for (int i = 0; i < ret->FirstCount; i++)
    {
        ret->pData[i] = (int*) malloc(ret->SecondCount * sizeof(int));
        //for (int j = 0; j < ret->SecondCount; j++)
        //{
            //ret->pData[i][j] = 0;
        //}
    }
    return ret;
}

Matrix* SumMatrices(Matrix* matrixA, Matrix* matrixB)
{
    assert(matrixA->SecondCount == matrixB->SecondCount);
    assert(matrixA->FirstCount == matrixB->FirstCount);

    Matrix* ret =
            CreateEmptyMatrix(matrixA->FirstCount, matrixA->SecondCount);

    for (int i = 0; i < ret->FirstCount; i++)
    {
        for (int j = 0; j < ret->SecondCount; j++)
        {
            ret->pData[i][j] = matrixA->pData[i][j] + matrixB->pData[i][j];
        }
    }

    return ret;
}

Matrix* GetMinor(Matrix* matrix, int firstIndex, int secondIndex)
{
    Matrix* ret = CreateEmptyMatrix(
            matrix->FirstCount - 1,
            matrix->SecondCount - 1);

    for (int i = 0; i < ret->FirstCount; i++)
    {
        for (int j = 0; j < ret->SecondCount; j++)
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
            ret->pData[i][j] = matrix->pData[oldi][oldj];
        }
    }
    return ret;
}

int CalculateDeterminant2x2(Matrix* matrix)
{
    assert(matrix->FirstCount == 2);
    assert(matrix->SecondCount == 2);

    int a = matrix->pData[0][0];
    int b = matrix->pData[1][0];
    int c = matrix->pData[0][1];
    int d = matrix->pData[1][1];
    return a * d - c * b;
}

int CalculateDeterminant(Matrix* matrix)
{
    assert(matrix->FirstCount == matrix->SecondCount);

    int n = matrix->FirstCount;

    if (n == 1)
    {
        return matrix->pData[0][0];
    }
    if (n == 2)
    {
        return CalculateDeterminant2x2(matrix);
    }
    if (n >= 3)
    {
        int ret = 0;
        for (int i = 0; i < matrix->FirstCount; i++)
        {
            int sign = (i % 2) ? -1 : 1;
            Matrix* minor = GetMinor(matrix, 0, i);
            int det = CalculateDeterminant(minor);
            int firstrow = matrix->pData[0][i];
            ret += sign * firstrow * det;
            FreeMatrix(minor);
        }
        return ret;
    }
}

void FreeMatrix(Matrix* matrix)
{
    for (int i = 0; i < matrix->FirstCount; i++)
    {
        free(matrix->pData[i]);
    }
    free(matrix->pData);
    free(matrix);
}