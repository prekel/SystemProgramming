#include <stdio.h>
#include <malloc.h>

#include "Input.h"

int main()
{
    while (true)
    {
        char* line = InputLineRealloc(10);
        printf("%s\n", line);
        free(line);
    }
    return 0;
}
