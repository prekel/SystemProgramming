/// \file
/// \brief Реализация функций из Input.h
/// \details Реализация функций из Input.h.

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <stdarg.h>

#include "Input.h"

char* InputLineRealloc(int stepSize, bool isFinalReallocRequired)
{
    assert(stepSize >= 2);
    unsigned int currentSize = stepSize;
    char* string = (char*) malloc((currentSize + 1) * sizeof(char));
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
                string = realloc(string, currentSize * sizeof(char));
                assert(string);
            }
            break;
        }
        currentSize += stepSize;
        string = realloc(string, currentSize * sizeof(char));
        assert(string);
        currentStep = string + currentSize - stepSize - i++;
    }
    return string;
}

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
    return -1;
}

int CycleInputInt(int maxIntLength,
                  bool(* pChecker)(int),
                  char* formatToOutput,
                  ...)
{
    int number = -1;
    int position = -1;
    char* stringNumber = (char*) malloc(maxIntLength * sizeof(char));
    assert(stringNumber);
    while (true)
    {
        va_list vaPtr;
        va_start(vaPtr, formatToOutput);
        vprintf(formatToOutput, vaPtr);
        va_end(vaPtr);
        fflush(stdout);

        int inputLineCode = InputLine(stringNumber, maxIntLength);
        if (inputLineCode == -1) continue;
        int sscanfCode = sscanf(stringNumber, "%d%n", &number, &position);
        if (position != inputLineCode) continue;
        if (pChecker != NULL && !pChecker(number)) continue;
        if (sscanfCode > 0) break;
    }
    free(stringNumber);
    return number;
}

char* CycleInputString(bool (* pChecker)(char*), char* formatToOutput, ...)
{
    char* string = NULL;
    do
    {
        free(string);

        va_list vaPtr;
        va_start(vaPtr, formatToOutput);
        vprintf(formatToOutput, vaPtr);
        va_end(vaPtr);
        fflush(stdout);

        string = InputLineRealloc(10, true);
    } while (pChecker && !pChecker(string));
    return string;
}
