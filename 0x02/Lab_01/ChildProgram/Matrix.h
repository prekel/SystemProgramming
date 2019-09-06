#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix
{
    int SecondCount;
    int FirstCount;
    int** pData;
} Matrix;

Matrix* CreateEmptyMatrix(int firstCount, int secondCount);

Matrix* SumMatrices(Matrix* MatrixA, Matrix* MatrixB);

Matrix* GetMinor(Matrix* matrix, int firstIndex, int secondIndex);

int CalculateDeterminant2x2(Matrix* matrix);

int CalculateDeterminant(Matrix* matrix);

void FreeMatrix(Matrix* a);

#endif // MATRIX_H
