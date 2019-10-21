#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#include "Input.h"

#define M_1E9 1000000000

bool check1(int n)
{
    return 2 <= n && n < M_1E9;
}

int main()
{
    while (true)
    {
        char* line = InputLineRealloc(10, true);
        printf("%s\n", line);
        if (line[0] == '\0')
        {
            free(line);
            break;
        }
        free(line);
    }
    while (true)
    {
        int a = CycleInputInt("123: ", 10, NULL);
        printf("%d\n", a);
        if (a == -10)
        {
            break;
        }
    }
    return 0;
}
