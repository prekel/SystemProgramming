/// \file
/// \brief Реализация функций из Args.h
/// \details Реализация некоторых функций из Args.h.

#include <stdio.h>

#include "Args.h"

extern const char* g_HelpMessage;

void PrintHelp()
{
    printf("%s", g_HelpMessage);
}
