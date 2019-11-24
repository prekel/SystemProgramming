/// \file
/// \brief Реализация функций из ArgsPrivate.h
/// \details Реализация некоторых функций из ArgsPrivate.h.

#include <stdio.h>

#include "ArgsPrivate.h"

extern const char* g_OptHelpUsage;

void UnknownOptionInternal(char unknownOption)
{
    printf("Неизвестный параметр: %c, введите %s для справки\n",
           unknownOption, g_OptHelpUsage);
}
