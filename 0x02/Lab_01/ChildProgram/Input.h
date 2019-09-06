#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

int InputLine(char* str);

int CycleInputInt(char* output, bool(* checker)(int));

double CycleInputDouble(char* output, bool(* checker)(double));

#endif // INPUT_H
