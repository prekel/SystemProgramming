#include <stdio.h>

#include "ArgsPrivate.h"

extern char* g_OptHelpUsage;

void UnknownOptionInternal(char unknownOption)
{
    printf("Неизвестный параметр: %c, введите %s"
           " для справки\n", unknownOption, g_OptHelpUsage);
}
