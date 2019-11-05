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
#include "HexDump.h"

void AddCommandExec(Args* pArgs)
{
    assert(!pArgs->IsFormatGiven);

    int fd = pArgs->IsForceCreate
             ? CreateFile(pArgs->FileName, sizeof(Archipelago))
             : OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));

    Archipelago archipelago;
    FillArchipelago(&archipelago,
                    pArgs->IsNameGiven ? pArgs->Name : pArgs->pExtraArgs[0],
                    pArgs->IsCountIslandsGiven ? pArgs->CountIslands : atoi(
                            pArgs->pExtraArgs[1]),
                    pArgs->IsCountInhabitedIslandsGiven
                    ? pArgs->CountInhabitedIslands : atoi(
                            pArgs->pExtraArgs[2]));

    AddRecord(fd, &archipelago);

    if (pArgs->IsHexDumpRequired)
    {
        HexDump(fd);
    }

    CloseFile(fd);
}

void FormatCommandExec(Args* pArgs)
{
    assert(!pArgs->IsIsForceCreateGiven);
    assert(!pArgs->IsNameGiven);
    assert(!pArgs->IsCountIslandsGiven);
    assert(!pArgs->IsCountInhabitedIslandsGiven);

    int fd = pArgs->IsForceCreate
             ? CreateFile(pArgs->FileName, sizeof(Archipelago))
             : OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));

    Meta meta;
    ReadMeta(fd, &meta);
    for (int i = 0; i < meta.Count; i++)
    {
        Archipelago archipelago;
        ReadRecord(fd, &archipelago, i);
        printf(pArgs->Format, archipelago.Name, archipelago.CountIslands,
               archipelago.CountInhabitedIslands);
        printf("\n");
    }
    printf("\n");

    if (pArgs->IsHexDumpRequired)
    {
        HexDump(fd);
    }

    CloseFile(fd);
}