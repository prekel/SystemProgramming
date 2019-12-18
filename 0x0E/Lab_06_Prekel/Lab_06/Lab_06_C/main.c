// \file
// \brief Вариант 4.
// \details Дана целочисленная матрица размера M x N.
// Найти количество ее строк и столбцов, все элементы которых различны.

#include <stdio.h>
#include <malloc.h>

#include "Matrix.h"
#include "MatrixIO.h"

int main()
{
    int m;
    int n;

    ReadMN(&m, &n);

    int* pMatrix = (int*) malloc(m * n * sizeof (int));

    ReadMatrix(pMatrix, m, n);

    printf("\n");

    WriteMatrix(pMatrix, m, n);

    printf("Кол-во строк, все элементы которых различны: %d\n",
           CountDifferentLines(pMatrix, m, n));
    printf("Кол-во столбцов, все элементы которых различны: %d\n",
           CountDifferentRows(pMatrix, m, n));

    free(pMatrix);

    return 0;
}
