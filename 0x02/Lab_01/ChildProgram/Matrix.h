#ifndef MATRIX_H
#define MATRIX_H

struct Matrix
{
    int RowsCount;
    int ColumnsCount;
    int** pData;
};

struct Matrix* CreateEmptyMatrix(int rowsCount, int columnsCount);

struct Matrix* SumMatrices(struct Matrix* MatrixA, struct Matrix* MatrixB);

void FreeMatrix(struct Matrix* a);

#endif MATRIX_H
