#include "ReturnCodesLib.h"

char* ReturnCodeLibMessage(int returnCode)
{
    switch (returnCode)
    {
    case UNSUCCESSFUL:
        return UNSUCCESSFUL_MESSAGE;
    case ALLOCATION_ERROR:
        return ALLOCATION_ERROR_MESSAGE;
    default:
        return UNKNOWN_ERROR_MESSAGE;
    }
}