#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <stdarg.h>

#include "ParseInt.h"

bool TryParseInt(char* string, int* pResult)
{
    size_t length = strlen(string);

    int position;

    int sscanfReturns = sscanf(string, "%d%n", pResult, &position);

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
    if (!tryParseInt)
    {
        return 0;
    }
    return result;
}
