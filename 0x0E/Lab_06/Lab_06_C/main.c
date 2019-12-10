#include <stdio.h>
#include <malloc.h>

#include "Matrix.h"
#include "MatrixIO.h"

int main()
{
    int m;
    int n;

    ReadMN(&m, &n);

    int* pMatrix = (int*) malloc(m * n * sizeof(int));

    ReadMatrix(pMatrix, m, n);

    WriteMatrix(pMatrix, m, n);

    int countLine = CountDifferentLines(pMatrix, m, n);
    printf("\nКол-во строк, все элементы которых различны: %d\n", countLine);
    int countRow = CountDifferentRows(pMatrix, m, n);
    printf("Кол-во столбцов, все элементы которых различны: %d\n", countRow);

    free(pMatrix);

    return 0;
}
