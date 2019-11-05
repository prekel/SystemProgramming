#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Archipelago.h"
#include "Commands.h"
#include "File.h"
#include "Args.h"
#include "Utils.h"

Args* CreateArgs()
{
    Args* pArgs = (Args*) malloc(sizeof(Args));

    pArgs->IsFileNameGiven = false;
    pArgs->FileName = DEFAULT_FILENAME;

    pArgs->IsIsForceCreateGiven = false;
    pArgs->IsForceCreate = false;

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

    pArgs->IsIsOrGiven = false;
    pArgs->IsOr = false;

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

#define OPT_STRING ":f:pM:F:C:N:I:n:c:i:dsoh"

#define OPT_FILENAME 'f'
#define OPT_FORCE_CREATE 'p'
#define OPT_META_FORMAT 'M'
#define OPT_FORMAT 'F'
#define OPT_COUNT_FORMAT 'C'
#define OPT_OLD_NAME 'N'
#define OPT_INDEX 'I'
#define OPT_NAME 'n'
#define OPT_COUNT_ISLANDS 'c'
#define OPT_COUNT_INHABITED_ISLANDS 'i'
#define OPT_HEXDUMP 'd'
#define OPT_REMOVE_SWAP_WITH_LAST 's'
#define OPT_OR 'o'
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
            pArgs->FileName = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg));
            assert(pArgs->FileName);
            strcpy(pArgs->FileName, optarg);
            break;
        case OPT_FORCE_CREATE:
            pArgs->IsIsForceCreateGiven = true;
            pArgs->IsForceCreate = true;
            break;
        case OPT_META_FORMAT:
            pArgs->IsMetaFormatGiven = true;
            pArgs->MetaFormat = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg));
            assert(pArgs->MetaFormat);
            strcpy(pArgs->MetaFormat, optarg);
            break;
        case OPT_FORMAT:
            pArgs->IsFormatGiven = true;
            pArgs->Format = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg));
            assert(pArgs->Format);
            strcpy(pArgs->Format, optarg);
            break;
        case OPT_COUNT_FORMAT:
            pArgs->IsCountFormatGiven = true;
            pArgs->CountFormat = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg));
            assert(pArgs->CountFormat);
            strcpy(pArgs->CountFormat, optarg);
            break;
        case OPT_OLD_NAME:
            pArgs->IsOldNameGiven = true;
            pArgs->OldName = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg));
            assert(pArgs->OldName);
            strcpy(pArgs->OldName, optarg);
            break;
        case OPT_INDEX:
            pArgs->IsIndexGiven = true;
            pArgs->Index = ParseInt(optarg);
            break;
        case OPT_NAME:
            pArgs->IsNameGiven = true;
            pArgs->Name = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg));
            assert(pArgs->Name);
            strcpy(pArgs->Name, optarg);
            break;
        case OPT_COUNT_ISLANDS:
            pArgs->IsCountIslandsGiven = true;
            pArgs->CountIslands = ParseInt(optarg);
            break;
        case OPT_COUNT_INHABITED_ISLANDS:
            pArgs->IsCountInhabitedIslandsGiven = true;
            pArgs->CountInhabitedIslands = ParseInt(optarg);
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
        case OPT_HELP:
            printf("help\n");
            break;
        case OPT_UNKNOWN:
            printf("unknown option: %c\n", optopt);
            break;
        default:
            assert(false);
        }
    }

    pArgs->pExtraArgs = argv + optind;

    return pArgs;
}