#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool CheckAllDifferent(const int* pArray, int step, int size)
{
    int max = size * step;
    for (int i = 0; i < max; i += step)
    {
        for (int j = i + step; j < max; j += step)
        {
            if (pArray[i] == pArray[j])
            {
                return false;
            }
        }
    }
    return true;
}

int CountDifferentLines(int* pMatrix, int m, int n)
{
    int c = 0;
    for (int i = 0; i < m; i++)
    {
        bool check = CheckAllDifferent(pMatrix + i * n, 1, n);
        if (check)
        {
            c++;
        }
    }
    return c;
}

int CountDifferentRows(int* pMatrix, int m, int n)
{
    int c = 0;
    for (int i = 0; i < n; i++)
    {
        bool check = CheckAllDifferent(pMatrix + i, n, m);
        if (check)
        {
            c++;
        }
    }
    return c;
}

void ReadMN(int* pM, int* pN)
{
    printf("Введите M и N (кол-во строк и столбцов, a[M][N]): ");
    scanf("%d%d", pM, pN);
}

void ReadMatrix(int* pMatrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Введите a[%d][%d]: ", i, j);
            scanf("%d", &pMatrix[i * n + j]);
        }
    }
}

void WriteMatrix(int* pMatrix, int m, int n)
{
    printf("Матрица a[%d][%d]:\n", m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", pMatrix[i * n + j]);
        }
        printf("\n");
    }
}

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
