#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix
{
    int RowsCount;
    int ColumnsCount;
    int** pData;
} Matrix;

Matrix* CreateEmptyMatrix(int rowsCount, int columnsCount);

Matrix* SumMatrices(Matrix* MatrixA, Matrix* MatrixB);

Matrix* GetMinor(Matrix* matrix, int row, int column);

int CalculateDeterminant(Matrix* matrix);

void FreeMatrix(Matrix* a);

#endif // MATRIX_H
