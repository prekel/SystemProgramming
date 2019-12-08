#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Matrix.h"

bool Check(const int* pArray, int step, int size)
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

int CountRow(int* pMatrix, int m, int n)
{
    int c = 0;
    for (int i = 0; i < n; i++)
    {
        bool check = Check(pMatrix + i, n, m);
        if (check)
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
        bool check = Check(pMatrix + i * n, 1, n);
        if (check)
        {
            c++;
        }
    }
    return c;
}
