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

    int sscanfCode = sscanf(string, "%d%n", result, &position);

    if (position != length || sscanfCode < 0)
    {
        return false;
    }

    return true;
}

int ParseInt(char* string)
{
    int result;
    bool tryParseInt = TryParseInt(string, &result);
    assert(tryParseInt);
    return result;
}
