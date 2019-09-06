#ifndef LABWORK2_INPUT_H
#define LABWORK2_INPUT_H

#include <stdbool.h>

int input_line(char *str);

int cycle_input_int(char *output, bool(*checker)(int));

double cycle_input_double(char *output, bool(*checker)(double));

#endif //LABWORK2_INPUT_H
