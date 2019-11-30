/// \file
/// \brief Реализация функций из Utils.h
/// \details Реализация функций из Utils.h.

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <stdarg.h>

#include "Utils.h"

#define MIN_STEPSIZE 2

char* InputLineRealloc(int stepSize, bool isFinalReallocRequired)
{
    assert(stepSize >= MIN_STEPSIZE);
    unsigned int currentSize = stepSize;
    char* string = (char*) malloc((currentSize + 1) * sizeof (char));
    assert(string);
    char* currentStep = string;
    int i = 1;
    while (true)
    {
        char* fgetsReturns = fgets(currentStep, stepSize, stdin);
        assert(fgetsReturns);

        unsigned int stringLength = strlen(currentStep);

        if (currentStep[stringLength - 1] == '\n')
        {
            currentStep[stringLength - 1] = '\0';
            if (isFinalReallocRequired)
            {
                currentSize = strlen(string) + 1;
                string = realloc(string, currentSize * sizeof (char));
                assert(string);
            }
            break;
        }
        currentSize += stepSize;
        string = realloc(string, currentSize * sizeof (char));
        assert(string);
        currentStep = string + currentSize - stepSize - i++;
    }
    return string;
}

#define INPUTLINE_LESS_THAN_MAXSTRINGLENGTH -1

int InputLine(char* stringToInput, int maxStringLength)
{
    unsigned long stringLength = 0;
    bool isError = false;
    while (true)
    {
        char* fgetsReturn = fgets(stringToInput, maxStringLength, stdin);
        assert(fgetsReturn);

        stringLength = strlen(stringToInput);

        if (stringToInput[stringLength - 1] != '\n')
        {
            isError = true;
        }
        else
        {
            break;
        }
    }
    if (!isError)
    {
        stringToInput[stringLength - 1] = '\0';
        return (int) stringLength - 1;
    }
    return INPUTLINE_LESS_THAN_MAXSTRINGLENGTH;
}

#define MIN_MAXINTLENGTH 3

int CycleInputInt(int maxIntLength,
                  bool(* pChecker)(int),
                  char* formatToOutput,
                  ...)
{
    assert(maxIntLength >= MIN_MAXINTLENGTH);
    int number;
    int position = 0;
    char* stringNumber = (char*) malloc(maxIntLength * sizeof (char));
    assert(stringNumber);
    while (true)
    {
        va_list vaPtr;
        va_start(vaPtr, formatToOutput);
        vprintf(formatToOutput, vaPtr);
        va_end(vaPtr);
        fflush(stdout);

        int inputLineReturns = InputLine(stringNumber, maxIntLength);
        if (inputLineReturns < 0) continue;
        int sscanfReturns =
                sscanf(stringNumber, "%d%n", &number, &position);
        if (position != inputLineReturns) continue;
        if (pChecker != NULL && !pChecker(number)) continue;
        if (sscanfReturns > 0) break;
    }
    free(stringNumber);
    return number;
}


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
