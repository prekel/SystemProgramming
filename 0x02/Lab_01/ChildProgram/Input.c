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

int CycleInputInt(char* output, bool(* checker)(int))
{
    int n;
    char string_number[100];
    while (true)
    {
        printf("%s", output);
        fflush(stdout);
        //scanf("%s", string_number);
        InputLine(string_number);
        int code = sscanf(string_number, "%d", &n);
        if (!checker(n)) continue;
        if (code > 0) break;
    }
    return n;
}

double CycleInputDouble(char* output, bool(* checker)(double))
{
    double n;
    char string_number[100];
    while (true)
    {
        printf("%s", output);
        fflush(stdout);
        //scanf("%s", string_number);
        InputLine(string_number);
        int code = sscanf(string_number, "%lf", &n);
        if (!checker(n)) continue;
        if (code > 0) break;
    }
    return n;
}