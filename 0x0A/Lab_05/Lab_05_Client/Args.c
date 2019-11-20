/// \file
/// \brief Реализация функций из Args.h
/// \details Реализация функций из Args.h.

#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>

#ifdef _MSC_VER
#include "getopt.h"
#else
#include <unistd.h>
#endif

#include "Args.h"
#include "ParseInt.h"
#include "ReturnCodes.h"
#include "Input.h"
#include "Matrix.h"
#include "Socket.h"

#define DEFAULT_IP_ADDRESS "127.0.0.1"
#define DEFAULT_PORT 20522
#define DEFAULT_PORT_STR "20522"

#define PROTOCOL_UDP "udp"
#define PROTOCOL_TCP "tcp"
#define DEFAULT_PROTOCOL PROTOCOL_UDP
#define DEFAULT_SOCKET_TYPE SOCK_DGRAM
#define DEFAULT_IPPROTO IPPROTO_UDP

#define OPT_STRING ":a:p:P:n:M:N:h"

#define OPT_IP_ADDRESS 'a'
#define OPT_IP_ADDRESS_USAGE "-a целое.целое.целое.целое"
#define OPT_IP_ADDRESS_DESCRIPTION "IP-адрес сервера. По умолчанию " DEFAULT_IP_ADDRESS "."
#define OPT_PORT 'p'
#define OPT_PORT_USAGE "-p целое"
#define OPT_PORT_DESCRIPTION "Порт. По умолчанию " DEFAULT_PORT_STR "."
#define OPT_PROTOCOL 'P'
#define OPT_PROTOCOL_USAGE "-P строка"
#define OPT_PROTOCOL_DESCRIPTION "Протокол " PROTOCOL_UDP " с дейтаграммными сокетами или " PROTOCOL_TCP " с потоковыми. По умолчанию " DEFAULT_PROTOCOL "."
#define OPT_DEGREE 'n'
#define OPT_DEGREE_USAGE "-n целое"
#define OPT_DEGREE_DESCRIPTION "Степень матрицы."
#define OPT_FIRST_INDEX 'M'
#define OPT_FIRST_INDEX_USAGE "-M целое"
#define OPT_FIRST_INDEX_DESCRIPTION "Номер строки (первый индекс matrix[M][N])."
#define OPT_SECOND_INDEX 'N'
#define OPT_SECOND_INDEX_USAGE "-N целое"
#define OPT_SECOND_INDEX_DESCRIPTION "Номер столбца (второй индекс matrix[M][N])."
#define OPT_HELP 'h'
#define OPT_HELP_USAGE "-h"
#define OPT_HELP_DESCRIPTION "Требуется ли вывод справки."
#define OPT_UNKNOWN '?'

Args* CreateArgs()
{
    Args* pArgs = (Args*) malloc(sizeof(Args));
    RETURN_NULL_IF_NULLPTR(pArgs);

    pArgs->IsIpAddressGiven = false;
    pArgs->IpAddress = DEFAULT_IP_ADDRESS;

    pArgs->IsPortGiven = false;
    pArgs->Port = DEFAULT_PORT;

    pArgs->IsProtocolGiven = false;
    pArgs->Protocol = DEFAULT_PROTOCOL;
    pArgs->SocketType = DEFAULT_SOCKET_TYPE;
    pArgs->IpProto = DEFAULT_IPPROTO;
    pArgs->IsTcp = false;

    pArgs->IsDegreeGiven = false;
    pArgs->Degree = 0;

    pArgs->IsFirstIndexGiven = false;
    pArgs->FirstIndex = 0;

    pArgs->IsSecondIndexGiven = false;
    pArgs->SecondIndex = 0;

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
    if (pArgs->IsIpAddressGiven)
    {
        free(pArgs->IpAddress);
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
        case OPT_IP_ADDRESS:
            pArgs->IsIpAddressGiven = true;
            RETURN_NULL_IF_NULLPTR(pArgs->IpAddress = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg)));
            strcpy(pArgs->IpAddress, optarg);
            pArgs->CountValidArgs++;
            break;
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
        case OPT_DEGREE:
            pArgs->IsDegreeGiven = true;
            pArgs->Degree = ParseInt(optarg, &pArgs->CountValidArgs);
            pArgs->CountValidArgs++;
            break;
        case OPT_FIRST_INDEX:
            pArgs->IsFirstIndexGiven = true;
            pArgs->FirstIndex = ParseInt(optarg, &pArgs->CountValidArgs);
            pArgs->CountValidArgs++;
            break;
        case OPT_SECOND_INDEX:
            pArgs->IsSecondIndexGiven = true;
            pArgs->SecondIndex = ParseInt(optarg, &pArgs->CountValidArgs);
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

#define MAX_INT_LEN 12

static bool DegreeChecker(int n)
{
    return n >= 1;
}

static bool IndexChecker(int n)
{
    return n >= 0;
}

static bool ElementChecker(int n)
{
    return true;
}

int InputAllOption(Args* pArgs)
{
    if (!pArgs->IsDegreeGiven)
    {
        printf("Степерь матрицы натуральное число.\n");
        pArgs->Degree = CycleInputInt(MAX_INT_LEN,
                                      DegreeChecker,
                                      "Введите степень матрицы: ");
    }
    if (!pArgs->IsFirstIndexGiven)
    {
        printf("Индексы не менее 0 и не более %d.\n", pArgs->Degree - 1);
    }
    if (!pArgs->IsFirstIndexGiven)
    {
        do
        {
            pArgs->FirstIndex =
                    CycleInputInt(MAX_INT_LEN,
                                  IndexChecker,
                                  "Введите номер строки M (первый индекс matrix[M][N]): ");
        } while (pArgs->FirstIndex >= pArgs->Degree);
    }
    if (!pArgs->IsSecondIndexGiven)
    {
        do
        {
            pArgs->SecondIndex =
                    CycleInputInt(MAX_INT_LEN,
                                  IndexChecker,
                                  "Введите номер столбца N (второй индекс matrix[M][N]): ");
        } while (pArgs->SecondIndex >= pArgs->Degree);
    }

    return SUCCESSFUL;
}

int InputOrFillMatrix(Args* pArgs, Matrix* pMatrix)
{
    if (pArgs->pExtraArgs[0] == NULL)
    {
        for (int i = 0; i < pMatrix->FirstCount; i++)
        {
            for (int j = 0; j < pMatrix->SecondCount; j++)
            {
                pMatrix->pData[i][j] =
                        CycleInputInt(MAX_INT_LEN,
                                      ElementChecker,
                                      "Введите элемент матрицы m[%d][%d]: ",
                                      i, j);
            }
        }
    }
    else
    {
        int count = 0;
        int k = 0;
        for (int i = 0; i < pMatrix->FirstCount; i++)
        {
            for (int j = 0; j < pMatrix->SecondCount; j++)
            {
                if (pArgs->pExtraArgs[k] == NULL)
                {
                    return BAD_ARGS;
                }
                pMatrix->pData[i][j] = ParseInt(pArgs->pExtraArgs[k++],
                                                &count);
            }
        }
        if (count != pMatrix->FirstCount * pMatrix->SecondCount)
        {
            return BAD_VALUE;
        }
    }

    return SUCCESSFUL;
}

#define APP_NAME "Lab_05_Client"
#define HELP_SEP ": "
#define HELP_SUFFIX "\n"

#define HELP_MESSAGE \
"Использование: ./" APP_NAME " [опции...] [2 * n целых чисел - элементы матриц]" HELP_SUFFIX \
"Опции: " HELP_SUFFIX \
OPT_IP_ADDRESS_USAGE HELP_SEP OPT_IP_ADDRESS_DESCRIPTION HELP_SUFFIX \
OPT_PORT_USAGE HELP_SEP OPT_PORT_DESCRIPTION HELP_SUFFIX \
OPT_PROTOCOL_USAGE HELP_SEP OPT_PROTOCOL_DESCRIPTION HELP_SUFFIX \
OPT_DEGREE_USAGE HELP_SEP OPT_DEGREE_DESCRIPTION HELP_SUFFIX \
OPT_FIRST_INDEX_USAGE HELP_SEP OPT_FIRST_INDEX_DESCRIPTION HELP_SUFFIX \
OPT_SECOND_INDEX_USAGE HELP_SEP OPT_SECOND_INDEX_DESCRIPTION HELP_SUFFIX \
OPT_HELP_USAGE HELP_SEP OPT_HELP_DESCRIPTION HELP_SUFFIX \


void PrintHelp()
{
    printf(HELP_MESSAGE);
}
