/// \file
/// \brief Реализация функций из Input.h
/// \details Реализация функций из Input.h.

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

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
    unsigned int errorCode = 0;
    unsigned long stringLength = 0;
    while (errorCode == 0 || errorCode == 1)
    {
        char* fgetsReturn = fgets(stringToInput, maxStringLength, stdin);

        int isEof = feof(stdin);
        int isErr = ferror(stdin);

        if (isEof == 1)
        {
            errorCode |= 2u;
        }
        if (isErr == 1)
        {
            errorCode |= 4u;
        }
        if (fgetsReturn == NULL)
        {
            errorCode |= 8u;
        }
        if (errorCode > 1)
        {
            break;
        }

        stringLength = strlen(stringToInput);

        if (stringToInput[stringLength - 1] != '\n')
        {
            errorCode |= 1u;
        }
        else
        {
            break;
        }
    }
    if (errorCode == 0)
    {
        stringToInput[stringLength - 1] = '\0';
        return (int) stringLength - 1;
    }
    return -(int) errorCode;
}

int CycleInputInt(char* stringToOutput, bool (* pChecker)(int))
{
    int number = -1;
    int position = -1;
    while (true)
    {
        printf("%s", stringToOutput);
        fflush(stdout);

        char* str1 = InputLineRealloc(20, false);
        int sscanfCode = sscanf(str1, "%d%n", &number, &position);
        unsigned int inputLineCode = strlen(str1);
        free(str1);
        if (position != inputLineCode) continue;
        if (pChecker != NULL && !pChecker(number)) continue;
        if (sscanfCode > 0) break;
    }
    return number;
}
