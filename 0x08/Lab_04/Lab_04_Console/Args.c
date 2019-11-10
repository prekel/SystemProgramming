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

#include "Archipelago.h"
#include "Commands.h"
#include "RecordFile.h"
#include "Args.h"
#include "ParseInt.h"
#include "ReturnCodesLib.h"

Args* CreateArgs()
{
    Args* pArgs = (Args*) malloc(sizeof(Args));
    RETURN_NULL_IF_NULLPTR(pArgs);

    pArgs->IsFilePathGiven = false;
    pArgs->FilePath = DEFAULT_FILENAME;

    pArgs->IsReCreate = false;

    pArgs->IsOpenOrCreate = false;

    pArgs->IsMetaFormatGiven = false;
    pArgs->MetaFormat = DEFAULT_META_FORMAT;

    pArgs->IsFormatGiven = false;
    pArgs->Format = DEFAULT_FORMAT;

    pArgs->IsCountFormatGiven = false;
    pArgs->CountFormat = DEFAULT_COUNT_FORMAT;

    pArgs->IsOldNameGiven = false;
    pArgs->OldName = "";

    pArgs->IsIndexGiven = false;
    pArgs->Index = 0;

    pArgs->IsNameGiven = false;
    pArgs->Name = "";

    pArgs->IsCountIslandsGiven = false;
    pArgs->CountIslands = 0;

    pArgs->IsCountInhabitedIslandsGiven = false;
    pArgs->CountInhabitedIslands = 0;

    pArgs->IsHexDumpRequired = false;

    pArgs->IsRemoveSwapWithLast = false;

    pArgs->IsPrintRequired = false;

    pArgs->IsOr = false;

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
    if (pArgs->IsFilePathGiven)
    {
        free(pArgs->FilePath);
    }
    if (pArgs->IsMetaFormatGiven)
    {
        free(pArgs->MetaFormat);
    }
    if (pArgs->IsFormatGiven)
    {
        free(pArgs->Format);
    }
    if (pArgs->IsCountFormatGiven)
    {
        free(pArgs->CountFormat);
    }
    if (pArgs->IsOldNameGiven)
    {
        free(pArgs->OldName);
    }
    if (pArgs->IsNameGiven)
    {
        free(pArgs->Name);
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
        case OPT_FILENAME:
            pArgs->IsFilePathGiven = true;
            RETURN_NULL_IF_NULLPTR(pArgs->FilePath = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg)));
            strcpy(pArgs->FilePath, optarg);
            pArgs->CountValidArgs++;
            break;
        case OPT_RECREATE:
            pArgs->IsReCreate = true;
            pArgs->CountValidArgs++;
            break;
        case OPT_OPEN_OR_CREATE:
            pArgs->IsOpenOrCreate = true;
            pArgs->CountValidArgs++;
            break;
        case OPT_META_FORMAT:
            pArgs->IsMetaFormatGiven = true;
            RETURN_NULL_IF_NULLPTR(pArgs->MetaFormat = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg)));
            strcpy(pArgs->MetaFormat, optarg);
            pArgs->CountValidArgs++;
            break;
        case OPT_FORMAT:
            pArgs->IsFormatGiven = true;
            RETURN_NULL_IF_NULLPTR(pArgs->Format = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg)));
            strcpy(pArgs->Format, optarg);
            pArgs->CountValidArgs++;
            break;
        case OPT_COUNT_FORMAT:
            pArgs->IsCountFormatGiven = true;
            RETURN_NULL_IF_NULLPTR(pArgs->CountFormat = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg)));
            strcpy(pArgs->CountFormat, optarg);
            pArgs->CountValidArgs++;
            break;
        case OPT_OLD_NAME:
            pArgs->IsOldNameGiven = true;
            RETURN_NULL_IF_NULLPTR(pArgs->OldName = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg)));
            strcpy(pArgs->OldName, optarg);
            pArgs->CountValidArgs++;
            break;
        case OPT_INDEX:
            pArgs->IsIndexGiven = true;
            pArgs->Index = ParseInt(optarg, &pArgs->CountValidArgs);
            break;
        case OPT_HEXDUMP:
            pArgs->IsHexDumpRequired = true;
            pArgs->CountValidArgs++;
            break;
        case OPT_REMOVE_SWAP_WITH_LAST:
            pArgs->IsRemoveSwapWithLast = true;
            pArgs->CountValidArgs++;
            break;
        case OPT_OR:
            pArgs->IsOr = true;
            pArgs->CountValidArgs++;
            break;
        case OPT_PRINT:
            pArgs->IsPrintRequired = true;
            pArgs->CountValidArgs++;
            break;
        case OPT_HELP:
            pArgs->IsHelpGiven = true;
            pArgs->CountValidArgs++;
            break;
        case OPT_NAME:
            pArgs->IsNameGiven = true;
            RETURN_NULL_IF_NULLPTR(pArgs->Name = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg)));
            strcpy(pArgs->Name, optarg);
            pArgs->CountValidArgs++;
            break;
        case OPT_COUNT_ISLANDS:
            pArgs->IsCountIslandsGiven = true;
            pArgs->CountIslands = ParseInt(optarg, &pArgs->CountValidArgs);
            break;
        case OPT_COUNT_INHABITED_ISLANDS:
            pArgs->IsCountInhabitedIslandsGiven = true;
            pArgs->CountInhabitedIslands = ParseInt(optarg,
                                                    &pArgs->CountValidArgs);
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
