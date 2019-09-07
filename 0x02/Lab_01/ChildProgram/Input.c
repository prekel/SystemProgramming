/*! \file
 *
 *  \brief Implements functions of Input.h
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "Input.h"

#define MAX_STRING_LENGTH 50

int InputLine(char* str)
{
    fgets(str, MAX_STRING_LENGTH, stdin);
    int size = strlen(str);
    str[strlen(str) - 1] = '\0';
    return size;
}

int CycleInputInt(char* output, bool(* pChecker)(int))
{
    int n;
    char stringNumber[MAX_STRING_LENGTH];
    while (true)
    {
        printf("%s", output);
        fflush(stdout);

        InputLine(stringNumber);
        int code = sscanf(stringNumber, "%d", &n);
        if (!pChecker(n)) continue;
        if (code > 0) break;
    }
    return n;
}