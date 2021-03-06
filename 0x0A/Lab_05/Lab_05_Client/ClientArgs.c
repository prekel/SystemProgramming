/// \file
/// \brief Реализация функций из ClientArgs.h
/// \details Реализация функций из ClientArgs.h.

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

#include "ClientArgs.h"
#include "ReturnCodes.h"
#include "Utils.h"
#include "Matrix.h"
#include "Socket.h"
#include "ArgsPrivate.h"

#define OPT_STRING ":a:p:n:M:N:h"

#define OPT_IP_ADDRESS 'a'
#define OPT_IP_ADDRESS_USAGE "-a целое.целое.целое.целое"
#define OPT_IP_ADDRESS_DESCRIPTION "IP-адрес сервера. По умолчанию " DEFAULT_IP_ADDRESS "."
#define OPT_DEGREE 'n'
#define OPT_DEGREE_USAGE "-n целое"
#define OPT_DEGREE_DESCRIPTION "Степень матрицы."

Args* CreateArgs()
{
    Args* pArgs = (Args*) malloc(sizeof (Args));
    RETURN_NULL_IF_NULLPTR(pArgs);

    pArgs->IsIpAddressGiven = false;
    pArgs->IpAddress = DEFAULT_IP_ADDRESS;

    pArgs->IsPortGiven = false;
    pArgs->Port = DEFAULT_PORT;

    pArgs->IsDegreeGiven = false;
    pArgs->Degree = 0;

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
    while ((opt = getopt(argc, pArgv, OPT_STRING)) != UNSUCCESSFUL)
    {
        switch (opt)
        {
        case OPT_IP_ADDRESS:
            pArgs->IsIpAddressGiven = true;
            RETURN_NULL_IF_NULLPTR(pArgs->IpAddress = (char*) malloc(
                    (sizeof (char) + 1) * strlen(optarg)));
            strcpy(pArgs->IpAddress, optarg);
            pArgs->CountValidArgs++;
            break;
        case OPT_PORT:
            pArgs->IsPortGiven = true;
            pArgs->Port = ParseInt(optarg, &pArgs->CountValidArgs);
            pArgs->CountValidArgs++;
            break;
        case OPT_DEGREE:
            pArgs->IsDegreeGiven = true;
            pArgs->Degree = ParseInt(optarg, &pArgs->CountValidArgs);
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
                                      "Введите степень матриц: ");
    }
    return SUCCESSFUL;
}

#define ENTER_MATRIX_ELEMENT_MESSAGE "Введите элемент матрицы %s[%d][%d]: "

static void InputMatrix(Matrix* pMatrix, char* matrixName)
{
    for (int i = 0; i < pMatrix->FirstCount; i++)
    {
        for (int j = 0; j < pMatrix->SecondCount; j++)
        {
            pMatrix->ppData[i][j] =
                    CycleInputInt(MAX_INT_LEN,
                                  ElementChecker,
                                  ENTER_MATRIX_ELEMENT_MESSAGE,
                                  matrixName, i, j);
        }
    }
}

static int FillMatrix(Matrix* pMatrix, char** pElements)
{
    int count = 0;
    int k = 0;
    for (int i = 0; i < pMatrix->FirstCount; i++)
    {
        for (int j = 0; j < pMatrix->SecondCount; j++)
        {
            if (pElements[k] == NULL)
            {
                return BAD_ARGS;
            }
            pMatrix->ppData[i][j] = ParseInt(pElements[k++], &count);
        }
    }
    if (count != pMatrix->FirstCount * pMatrix->SecondCount)
    {
        return BAD_VALUE;
    }
    return SUCCESSFUL;
}

int InputOrFillMatrices(Args* pArgs, Matrix* pMatrixA, Matrix* pMatrixB)
{
    if (pArgs->pExtraArgs[0] == NULL)
    {
        printf("Элементы матриц - целые числа\n");
        InputMatrix(pMatrixA, "A");
        InputMatrix(pMatrixB, "B");
    }
    else
    {
        RETURN_IF_NOT_SUCCESSFUL(FillMatrix(pMatrixA, pArgs->pExtraArgs));
        RETURN_IF_NOT_SUCCESSFUL(FillMatrix(pMatrixB, pArgs->pExtraArgs
                                                      + pMatrixA->FirstCount *
                                                        pMatrixA->FirstCount));
    }
    return SUCCESSFUL;
}

#define APP_NAME "Lab_05_Client"

#define HELP_MESSAGE \
"Использование: " APP_NAME " [" OPT_IP_ADDRESS_USAGE "] [" OPT_PORT_USAGE \
"] [" OPT_DEGREE_USAGE "] [" OPT_HELP_USAGE \
"] [2 * n * n положительных целых чисел - элементы матриц]" HELP_SUFFIX \
"Опции: " HELP_SUFFIX \
OPT_IP_ADDRESS_USAGE HELP_SEP OPT_IP_ADDRESS_DESCRIPTION HELP_SUFFIX \
OPT_PORT_USAGE HELP_SEP OPT_PORT_DESCRIPTION HELP_SUFFIX \
OPT_DEGREE_USAGE HELP_SEP OPT_DEGREE_DESCRIPTION HELP_SUFFIX \
OPT_HELP_USAGE HELP_SEP OPT_HELP_DESCRIPTION HELP_SUFFIX \

const char* g_HelpMessage = HELP_MESSAGE;

const char* g_OptHelpUsage = OPT_HELP_USAGE;

void UnknownOption(Args* pArgs)
{
    UnknownOptionInternal(pArgs->UnknownOption);
}
