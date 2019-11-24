#include <stdio.h>

#include "Args.h"

extern const char* g_HelpMessage;

void PrintHelp()
{
    printf("%s", g_HelpMessage);
}
