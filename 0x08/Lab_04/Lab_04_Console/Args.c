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
#include "File.h"
#include "Args.h"
#include "Utils.h"
#include "ReturnCodesLib.h"

Args* CreateArgs()
{
    Args* pArgs = (Args*) malloc(sizeof(Args));

    pArgs->IsFileNameGiven = false;
    pArgs->FileName = DEFAULT_FILENAME;

    pArgs->IsIsReCreateGiven = false;
    pArgs->IsReCreate = false;

    pArgs->IsIsOpenOrCreateGiven = false;
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

    pArgs->IsIsHexDumpRequiredGiven = false;
    pArgs->IsHexDumpRequired = false;

    pArgs->IsIsRemoveSwapWithLastGiven = false;
    pArgs->IsRemoveSwapWithLast = false;

    pArgs->IsIsPrintRequiredGiven = false;
    pArgs->IsPrintRequired = false;

    pArgs->IsIsOrGiven = false;
    pArgs->IsOr = false;

    pArgs->IsHelpGiven = false;

    pArgs->IsUnknownOptionGiven = false;
    pArgs->UnknownOption = '\0';

    return pArgs;
}

void DestroyArgs(Args* pArgs)
{
    if (pArgs->IsFileNameGiven)
    {
        free(pArgs->FileName);
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

#define OPT_STRING ":f:rpM:F:C:N:I:n:c:i:DsoPh"

#define OPT_FILENAME 'f'
#define OPT_RECREATE 'r'
#define OPT_OPEN_OR_CREATE 'p'
#define OPT_META_FORMAT 'M'
#define OPT_FORMAT 'F'
#define OPT_COUNT_FORMAT 'C'
#define OPT_OLD_NAME 'N'
#define OPT_INDEX 'I'
#define OPT_NAME 'n'
#define OPT_COUNT_ISLANDS 'c'
#define OPT_COUNT_INHABITED_ISLANDS 'i'
#define OPT_HEXDUMP 'D'
#define OPT_REMOVE_SWAP_WITH_LAST 's'
#define OPT_OR 'o'
#define OPT_PRINT 'P'
#define OPT_HELP 'h'
#define OPT_UNKNOWN '?'

Args* ParseArgs(int argc, char** argv)
{
    Args* pArgs = CreateArgs();

    int opt;
    while ((opt = getopt(argc, argv, OPT_STRING)) != -1)
    {
        switch (opt)
        {
        case OPT_FILENAME:
            pArgs->IsFileNameGiven = true;
            RETURN_NULL_IF_NULLPTR(pArgs->FileName = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg)));
            //assert(pArgs->FileName);
            strcpy(pArgs->FileName, optarg);
            break;
        case OPT_RECREATE:
            pArgs->IsIsReCreateGiven = true;
            pArgs->IsReCreate = true;
            break;
        case OPT_OPEN_OR_CREATE:
            pArgs->IsIsOpenOrCreateGiven = true;
            pArgs->IsOpenOrCreate = true;
            break;
        case OPT_META_FORMAT:
            pArgs->IsMetaFormatGiven = true;
            RETURN_NULL_IF_NULLPTR(pArgs->MetaFormat = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg)));
            //assert(pArgs->MetaFormat);
            strcpy(pArgs->MetaFormat, optarg);
            break;
        case OPT_FORMAT:
            pArgs->IsFormatGiven = true;
            RETURN_NULL_IF_NULLPTR(pArgs->Format = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg)));
            //assert(pArgs->Format);
            strcpy(pArgs->Format, optarg);
            break;
        case OPT_COUNT_FORMAT:
            pArgs->IsCountFormatGiven = true;
            RETURN_NULL_IF_NULLPTR(pArgs->CountFormat = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg)));
            //assert(pArgs->CountFormat);
            strcpy(pArgs->CountFormat, optarg);
            break;
        case OPT_OLD_NAME:
            pArgs->IsOldNameGiven = true;
            RETURN_NULL_IF_NULLPTR(pArgs->OldName = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg)));
            //assert(pArgs->OldName);
            strcpy(pArgs->OldName, optarg);
            break;
        case OPT_INDEX:
            pArgs->IsIndexGiven = true;
            pArgs->Index = ParseInt(optarg, NULL);
            break;
        case OPT_NAME:
            pArgs->IsNameGiven = true;
            RETURN_NULL_IF_NULLPTR(pArgs->Name = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg)));
            //assert(pArgs->Name);
            strcpy(pArgs->Name, optarg);
            break;
        case OPT_COUNT_ISLANDS:
            pArgs->IsCountIslandsGiven = true;
            pArgs->CountIslands = ParseInt(optarg, NULL);
            break;
        case OPT_COUNT_INHABITED_ISLANDS:
            pArgs->IsCountInhabitedIslandsGiven = true;
            pArgs->CountInhabitedIslands = ParseInt(optarg, NULL);
            break;
        case OPT_HEXDUMP:
            pArgs->IsIsHexDumpRequiredGiven = true;
            pArgs->IsHexDumpRequired = true;
            break;
        case OPT_REMOVE_SWAP_WITH_LAST:
            pArgs->IsIsRemoveSwapWithLastGiven = true;
            pArgs->IsRemoveSwapWithLast = true;
            break;
        case OPT_OR:
            pArgs->IsIsOrGiven = true;
            pArgs->IsOr = true;
            break;
        case OPT_PRINT:
            pArgs->IsIsPrintRequiredGiven = true;
            pArgs->IsPrintRequired = true;
            break;
        case OPT_HELP:
            pArgs->IsHelpGiven = true;
            break;
        case OPT_UNKNOWN:
            pArgs->IsUnknownOptionGiven = true;
            pArgs->UnknownOption = (char) optopt;
            break;
        default:
            pArgs->IsUnknownOptionGiven = true;
            break;
        }
    }

    pArgs->pExtraArgs = argv + optind;

    return pArgs;
}
