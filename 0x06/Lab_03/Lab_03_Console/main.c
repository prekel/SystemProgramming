#include <stdio.h>
#include <malloc.h>

#include "Input.h"

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
        int a = CycleInputInt("123: ", NULL);
        printf("%d\n", a);
        if (a == -10)
        {
            break;
        }
    }
    return 0;
}
