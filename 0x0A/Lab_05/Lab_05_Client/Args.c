/// \file
/// \brief Реализация функций из Args.h
/// \details Реализация функций из Args.h.

#include <malloc.h>
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
#include "ReturnCodesLib.h"
#include "Input.h"
#include "Matrix.h"

Args* CreateArgs()
{
    Args* pArgs = (Args*) malloc(sizeof(Args));
    RETURN_NULL_IF_NULLPTR(pArgs);

    pArgs->IsIpAddressGiven = false;
    pArgs->IpAddress = DEFAULT_IP_ADDRESS;

    pArgs->IsPortGiven = false;
    pArgs->Port = DEFAULT_PORT;

    pArgs->IsDegreeGiven = false;
    pArgs->Degree = 0;

    pArgs->IsFirstIndexGiven = false;
    pArgs->FirstIndex = 0;

    pArgs->IsSecondIndexGiven = false;
    pArgs->SecondIndex = 0;

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
        pArgs->Degree = CycleInputInt(MAX_INT_LEN,
                                      DegreeChecker,
                                      "Введите степень матрицы: ");
    }
    if (!pArgs->IsFirstIndexGiven)
    {
        pArgs->FirstIndex = CycleInputInt(MAX_INT_LEN,
                                          IndexChecker,
                                          "Введите первый индекс матрицы: ");
    }
    if (!pArgs->IsSecondIndexGiven)
    {
        pArgs->SecondIndex = CycleInputInt(MAX_INT_LEN,
                                           IndexChecker,
                                           "Введите второй индекс матрицы: ");
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
                pMatrix->pData[i][j] = CycleInputInt(MAX_INT_LEN,
                        ElementChecker,
                        "Введите элемент матрицы m[%d][%d]\n",
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
                pMatrix->pData[i][j] = ParseInt(pArgs->pExtraArgs[k++], &count);
            }
        }
        if (count != pMatrix->FirstCount * pMatrix->SecondCount)
        {
            return BAD_VALUE;
        }
    }

    return SUCCESSFUL;
}
