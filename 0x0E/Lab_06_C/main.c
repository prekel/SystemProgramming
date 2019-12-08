#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool Check(const int* pArray, int step, int size)
{
    for (int i = 0; i < size * step; i += step)
    {
        for (int j = i + step; j < size * step; j += step)
        {
            if (pArray[i] == pArray[j])
            {
                return false;
            }
        }
    }
    return true;
}

void ReadMatrix(int* pMatrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &pMatrix[i * n + j]);
        }
    }
}

void ReadMN(int* pM, int* pN)
{
    scanf("%d", pM);
    scanf("%d", pN);
}

int CountRow(int* pMatrix, int m, int n)
{
    int c = 0;
    for (int i = 0; i < n; i++)
    {
        if (Check(pMatrix + i, n, m))
        {
            c++;
        }
    }
    return c;
}

int CountLine(int* pMatrix, int m, int n)
{
    int c = 0;
    for (int i = 0; i < m; i++)
    {
        if (Check(pMatrix + i * n, 1, n))
        {
            c++;
        }
    }
    return c;
}

int main()
{
    int m;
    int n;

    ReadMN(&m, &n);

    int* pMatrix = malloc(m * n * sizeof(int));

    ReadMatrix(pMatrix, m, n);

    printf("%d\n", CountRow(pMatrix, m, n));
    printf("%d\n", CountLine(pMatrix, m, n));

    free(pMatrix);

    return 0;
}
