#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <stdarg.h>

#include "Utils.h"

bool TryParseInt(char* string, int* result)
{
    size_t length = strlen(string);

    int position;

    int sscanfReturns = sscanf(string, "%d%n", result, &position);

    if (position != length || sscanfReturns < 0)
    {
        return false;
    }

    return true;
}

int ParseInt(char* string, int* pSuccessfulCount)
{
    int result;
    bool tryParseInt = TryParseInt(string, &result);
    if (pSuccessfulCount != NULL && tryParseInt)
    {
        (*pSuccessfulCount)++;
    }
    return result;
}
