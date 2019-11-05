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

Args* CreateArgs()
{
    Args* pArgs = (Args*) malloc(sizeof(Args));

    pArgs->IsFileNameGiven = false;
    pArgs->FileName = DEFAULT_FILENAME;

    pArgs->IsIsForceCreateGiven = false;
    pArgs->IsForceCreate = false;

    pArgs->IsFormatGiven = false;
    pArgs->Format = DEFAULT_FORMAT;

    pArgs->IsNameGiven = false;
    pArgs->Name = "";

    pArgs->IsCountIslandsGiven = false;
    pArgs->CountIslands = 0;

    pArgs->IsCountInhabitedIslandsGiven = false;
    pArgs->CountInhabitedIslands = 0;

    return pArgs;
}

void DestroyArgs(Args* pArgs)
{
    if (pArgs->IsFileNameGiven)
    {
        free(pArgs->FileName);
    }
    if (pArgs->IsFormatGiven)
    {
        free(pArgs->Format);
    }
    if (pArgs->IsNameGiven)
    {
        free(pArgs->Name);
    }
    free(pArgs);
}

#define OPT_STRING ":f:pF:n:c:i:h"

Args* ParseArgs(int argc, char** argv)
{
    Args* pArgs = CreateArgs();

    int opt;
    while ((opt = getopt(argc, argv, OPT_STRING)) != -1)
    {
        switch (opt)
        {
        case 'f':
            pArgs->IsFileNameGiven = true;
            pArgs->FileName = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg));
            assert(pArgs->FileName);
            strcpy(pArgs->FileName, optarg);
            break;
        case 'p':
            pArgs->IsIsForceCreateGiven = true;
            pArgs->IsForceCreate = true;
            break;
        case 'F':
            pArgs->IsFormatGiven = true;
            pArgs->Format = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg));
            assert(pArgs->Format);
            strcpy(pArgs->Format, optarg);
            break;
        case 'n':
            pArgs->IsNameGiven = true;
            pArgs->Name = (char*) malloc(
                    (sizeof(char) + 1) * strlen(optarg));
            assert(pArgs->Name);
            strcpy(pArgs->Name, optarg);
            break;
        case 'c':
            pArgs->IsCountIslandsGiven = true;
            pArgs->CountIslands = atoi(optarg);
            break;
        case 'i':
            pArgs->IsCountInhabitedIslandsGiven = true;
            pArgs->CountInhabitedIslands = atoi(optarg);
            break;
        case 'h':
            pArgs->IsIsHexDumpRequiredGiven = true;
            pArgs->IsHexDumpRequired = true;
            break;
        case ':':
            printf("option needs a value\n");
            break;
        case '?':
            printf("unknown option: %c\n", optopt);
            break;
        }
    }

    pArgs->pExtraArgs = argv + optind;

    return pArgs;
}