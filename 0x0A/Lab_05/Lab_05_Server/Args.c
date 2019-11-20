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
#include "Socket.h"

#define DEFAULT_PORT 20522
#define DEFAULT_PORT_STR "20522"

#define PROTOCOL_UDP "udp"
#define PROTOCOL_TCP "tcp"
#define DEFAULT_PROTOCOL PROTOCOL_UDP
#define DEFAULT_SOCKET_TYPE SOCK_DGRAM
#define DEFAULT_IPPROTO IPPROTO_UDP

#define OPT_STRING ":p:P:h"

#define OPT_PORT 'p'
#define OPT_PORT_USAGE "-p целое"
#define OPT_PORT_DESCRIPTION "Порт. По умолчанию " DEFAULT_PORT_STR "."
#define OPT_PROTOCOL 'P'
#define OPT_PROTOCOL_USAGE "-P строка"
#define OPT_PROTOCOL_DESCRIPTION "Протокол " PROTOCOL_UDP " с дейтаграммными сокетами или " PROTOCOL_TCP " с потоковыми. По умолчанию " DEFAULT_PROTOCOL "."
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

    pArgs->IsProtocolGiven = false;
    pArgs->Protocol = DEFAULT_PROTOCOL;
    pArgs->SocketType = DEFAULT_SOCKET_TYPE;
    pArgs->IpProto = DEFAULT_IPPROTO;
    pArgs->IsTcp = false;

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
        case OPT_PROTOCOL:
            pArgs->IsProtocolGiven = true;
            RETURN_NULL_IF_NULLPTR(pArgs->Protocol = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg)));
            strcpy(pArgs->Protocol, optarg);
            if (strcmp(pArgs->Protocol, PROTOCOL_TCP) == 0)
            {
                pArgs->IpProto = IPPROTO_TCP;
                pArgs->SocketType = SOCK_STREAM;
                pArgs->IsTcp = true;
                pArgs->CountValidArgs++;
            }
            else if (strcmp(pArgs->Protocol, PROTOCOL_UDP) == 0)
            {
                pArgs->CountValidArgs++;
            }
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
"Использование: ./" APP_NAME " ["OPT_PORT_USAGE "] [" OPT_PROTOCOL_USAGE "] [" OPT_HELP_USAGE "] " HELP_SUFFIX \
"Опции: " HELP_SUFFIX \
OPT_PORT_USAGE HELP_SEP OPT_PORT_DESCRIPTION HELP_SUFFIX \
OPT_PROTOCOL_USAGE HELP_SEP OPT_PROTOCOL_DESCRIPTION HELP_SUFFIX \
OPT_HELP_USAGE HELP_SEP OPT_HELP_DESCRIPTION HELP_SUFFIX \

void PrintHelp()
{
    printf(HELP_MESSAGE);
}

void UnknownOption(Args* pArgs)
{
    printf("Неизвестный параметр: %c\n", pArgs->UnknownOption);
}
