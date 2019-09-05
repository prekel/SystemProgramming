#ifndef MATRIX_H
#define MATRIX_H

struct Matrix
{
	int RowCount;
	int ColumnsCount;
	int** pData;
};

struct Matrix CreateEmptyMatrix(int n, int m);
void FreeMatrix(struct Matrix* a);

#endif MATRIX_H
