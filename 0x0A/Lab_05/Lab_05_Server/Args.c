/// \file
/// \brief Реализация функций из Args.h
/// \details Реализация функций из Args.h.

#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#ifdef _MSC_VER
#include "getopt.h"
#else
#include <unistd.h>
#endif

#include "Args.h"
#include "ParseInt.h"
#include "ReturnCodes.h"

#define DEFAULT_PORT 20522

#define OPT_STRING ":p:h"

#define OPT_PORT 'p'
#define OPT_PORT_USAGE "-p целое"
#define OPT_PORT_DESCRIPTION "Порт."
#define OPT_HELP 'h'
#define OPT_HELP_USAGE "-h"
#define OPT_HELP_DESCRIPTION "Требуется ли вывод справки."
#define OPT_UNKNOWN '?'

Args* CreateArgs()
{
    Args* pArgs = (Args*) malloc(sizeof(Args));
    RETURN_NULL_IF_NULLPTR(pArgs);

    pArgs->IsPortGiven = false;
    pArgs->Port = DEFAULT_PORT;

    pArgs->IsHelpGiven = false;

    pArgs->IsUnknownOptionGiven = false;
    pArgs->UnknownOption = '\0';

    pArgs->CountArgs = 0;
    pArgs->CountValidArgs = 0;

    return pArgs;
}

void DestroyArgs(Args* pArgs)
{
    if (pArgs == NULL)
    {
        return;
    }
    free(pArgs);
}

Args* ParseArgs(int argc, char** pArgv)
{
    Args* pArgs = CreateArgs();
    RETURN_NULL_IF_NULLPTR(pArgs);

    int opt;
    while ((opt = getopt(argc, pArgv, OPT_STRING)) != -1)
    {
        switch (opt)
        {
        case OPT_PORT:
            pArgs->IsPortGiven = true;
            pArgs->Port = ParseInt(optarg, &pArgs->CountValidArgs);
            pArgs->CountValidArgs++;
            break;
        case OPT_HELP:
            pArgs->IsHelpGiven = true;
            pArgs->CountValidArgs++;
            break;
        case OPT_UNKNOWN:
            pArgs->IsUnknownOptionGiven = true;
            pArgs->UnknownOption = (char) optopt;
            pArgs->CountValidArgs++;
            break;
        default:
            pArgs->IsUnknownOptionGiven = true;
            break;
        }
        pArgs->CountArgs++;
    }

    pArgs->pExtraArgs = pArgv + optind;

    return pArgs;
}

#define APP_NAME "Lab_05_Server"
#define HELP_SEP ": "
#define HELP_SUFFIX "\n"

#define HELP_MESSAGE \
"Использование: ./" APP_NAME " [опции...]" HELP_SUFFIX \
"Опции: " HELP_SUFFIX \
OPT_PORT_USAGE HELP_SEP OPT_PORT_DESCRIPTION HELP_SUFFIX \
OPT_HELP_USAGE HELP_SEP OPT_HELP_DESCRIPTION HELP_SUFFIX \

void PrintHelp()
{
    printf(HELP_MESSAGE);
}
