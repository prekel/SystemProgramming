#include <stdio.h>
#include <malloc.h>

#include "Matrix.h"
#include "MatrixIO.h"

int main()
{
    int m;
    int n;

    ReadMN(&m, &n);

    int pMatrix[m * n];

    ReadMatrix(pMatrix, m, n);

    printf("\n");

    WriteMatrix(pMatrix, m, n);

    printf("Кол-во строк, все элементы которых различны: %d\n",
           CountDifferentLines(pMatrix, m, n));
    printf("Кол-во столбцов, все элементы которых различны: %d\n",
           CountDifferentRows(pMatrix, m, n));

    return 0;
}
