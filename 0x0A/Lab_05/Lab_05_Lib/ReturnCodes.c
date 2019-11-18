#include <stdio.h>

#include "ReturnCodes.h"

char* ReturnCodeMessage(int returnCode)
{
    switch (returnCode)
    {
    case UNSUCCESSFUL:
        return UNSUCCESSFUL_MESSAGE;
    case BAD_VALUE:
        return BAD_VALUE_MESSAGE;
    case BAD_ARGS:
        return BAD_ARGS_MESSAGE;
    case ALLOCATION_ERROR:
        return ALLOCATION_ERROR_MESSAGE;
    default:
        return UNKNOWN_ERROR_MESSAGE;
    }
}

void PrintReturnCodeMessage(int returnCode)
{
    fprintf(stderr, "%s", ReturnCodeMessage(returnCode));
}
