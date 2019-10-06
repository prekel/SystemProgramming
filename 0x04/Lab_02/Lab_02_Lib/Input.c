/*! \file
 *
 *  \brief Реализация функций из Input.h
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#include "Macro.h"
#include "Input.h"

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

int CycleInputInt(char* stringToOutput, int maxStringLength,
                  bool(* pChecker)(int))
{
    int number = -1;
    int position = -1;
    char* stringNumber = (char*) malloc(maxStringLength * sizeof(char));
    FAILURE_IF_NULLPTR(stringNumber);
    while (true)
    {
        printf("%s", stringToOutput);
        fflush(stdout);

        int inputLineCode = InputLine(stringNumber, maxStringLength);
        if (inputLineCode == -1) continue;
        if (inputLineCode < 0)
        {
            fprintf(stderr, "Ошибка при вводе\n");
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
        int sscanfCode = sscanf(stringNumber, "%d%n", &number, &position);
        if (position != inputLineCode) continue;
        if (pChecker != NULL && !pChecker(number)) continue;
        if (sscanfCode > 0) break;
    }
    free(stringNumber);
    return number;
}