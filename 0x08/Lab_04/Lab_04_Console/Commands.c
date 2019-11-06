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
#include "Utils.h"

void AddCommandExec(Args* pArgs)
{
    assert(!pArgs->IsMetaFormatGiven);
    assert(!pArgs->IsFormatGiven);

    int fd = pArgs->IsForceCreate
             ? CreateFile1(pArgs->FileName, sizeof(Archipelago))
             : OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));

    Archipelago archipelago;
    FillArchipelago(&archipelago,
                    pArgs->IsNameGiven
                    ? pArgs->Name
                    : pArgs->pExtraArgs[0],
                    pArgs->IsCountIslandsGiven
                    ? pArgs->CountIslands
                    : ParseInt(pArgs->pExtraArgs[1]),
                    pArgs->IsCountInhabitedIslandsGiven
                    ? pArgs->CountInhabitedIslands
                    : ParseInt(pArgs->pExtraArgs[2]));

    Meta meta;
    int readMeta = ReadMeta(fd, &meta);
    assert(readMeta != READ_WRITE_UNSUCCESSFUL);

    AddArchipelago(fd, &meta, &archipelago);

    if (pArgs->IsHexDumpRequired)
    {
        HexDump(fd);
    }

    CloseFile1(fd);
}

void ModifyCommandExec(Args* pArgs)
{
    assert(!pArgs->IsMetaFormatGiven);
    assert(!pArgs->IsFormatGiven);
    assert(pArgs->IsIndexGiven || pArgs->IsOldNameGiven);
    assert(!(pArgs->IsIndexGiven && pArgs->IsOldNameGiven));
    assert(pArgs->IsNameGiven || pArgs->IsCountIslandsGiven ||
           pArgs->IsCountInhabitedIslandsGiven);
    assert(pArgs->IsIndexGiven && pArgs->Index >= 0);

    int fd = pArgs->IsForceCreate
             ? CreateFile1(pArgs->FileName, sizeof(Archipelago))
             : OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));

    Meta meta;
    int readMeta = ReadMeta(fd, &meta);
    assert(readMeta != READ_WRITE_UNSUCCESSFUL);

    assert(pArgs->IsIndexGiven && pArgs->Index < meta.Count);

    int index = pArgs->IsIndexGiven
                ? pArgs->Index
                : IndexByName(fd, &meta, pArgs->OldName);

    assert(index != NOT_FOUND);

    if (pArgs->IsNameGiven)
    {
        ModifyName(fd, &meta, index, pArgs->Name);
    }
    if (pArgs->IsCountIslandsGiven)
    {
        ModifyCountIslands(fd, &meta, index, pArgs->CountIslands);
    }
    if (pArgs->IsCountInhabitedIslandsGiven)
    {
        ModifyCountInhabitedIslands(fd, &meta, index,
                                    pArgs->CountInhabitedIslands);
    }

    if (pArgs->IsHexDumpRequired)
    {
        HexDump(fd);
    }

    CloseFile1(fd);
}

void RemoveCommandExec(Args* pArgs)
{
    assert(!pArgs->IsMetaFormatGiven);
    assert(!pArgs->IsFormatGiven);
    assert(pArgs->IsIndexGiven || pArgs->IsNameGiven);
    assert(!(pArgs->IsIndexGiven && pArgs->IsNameGiven));
    assert(pArgs->IsIndexGiven && pArgs->Index >= 0);

    int fd = pArgs->IsForceCreate
             ? CreateFile1(pArgs->FileName, sizeof(Archipelago))
             : OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));

    Meta meta;
    int readMeta = ReadMeta(fd, &meta);
    assert(readMeta != READ_WRITE_UNSUCCESSFUL);

    assert(pArgs->IsIndexGiven && pArgs->Index < meta.Count);

    int index = pArgs->IsIndexGiven
                ? pArgs->Index
                : IndexByName(fd, &meta, pArgs->Name);

    assert(index != NOT_FOUND);

    if (pArgs->IsRemoveSwapWithLast)
    {
        RemoveSwapWithLast(fd, &meta, index);
    }
    else
    {
        RemoveShift(fd, &meta, index);
    }

    if (pArgs->IsHexDumpRequired)
    {
        HexDump(fd);
    }

    CloseFile1(fd);
}

void DeleteCommandExec(Args* pArgs)
{
    bool isExist = IsExist(pArgs->FileName);
    assert(isExist);

    int deleteFile = DeleteFile(pArgs->FileName);
    assert(deleteFile == 0);
}

void HasUninhabitedCommandExec(Args* pArgs)
{
    assert(!pArgs->IsMetaFormatGiven);
    assert(!pArgs->IsFormatGiven);
    assert(pArgs->IsIndexGiven || pArgs->IsOldNameGiven);
    assert(!(pArgs->IsIndexGiven && pArgs->IsOldNameGiven));

    int fd = pArgs->IsForceCreate
             ? CreateFile1(pArgs->FileName, sizeof(Archipelago))
             : OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));

    Meta meta;
    int readMeta = ReadMeta(fd, &meta);
    assert(readMeta != READ_WRITE_UNSUCCESSFUL);

    bool has = false;
    for (int i = 0; i < meta.Count; i++)
    {
        Archipelago archipelago;
        ReadArchipelago(fd, &meta, &archipelago, i);
        if (archipelago.CountInhabitedIslands == 0)
        {
            has = true;
            break;
        }
    }

    if (has)
    {
        printf("Имеются архипелаги, состоящие только из необитаемых "
               "островов\n");
    }
    else
    {
        printf("Отсутствуют архипелаги, состоящие только из необитаемых "
               "островов\n");
    }

    if (pArgs->IsHexDumpRequired)
    {
        HexDump(fd);
    }

    CloseFile1(fd);
}

void PrintCommandExec(Args* pArgs)
{
    int fd = pArgs->IsForceCreate
             ? CreateFile1(pArgs->FileName, sizeof(Archipelago))
             : OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));

    Meta meta;
    int readMeta = ReadMeta(fd, &meta);
    assert(readMeta != READ_WRITE_UNSUCCESSFUL);

    printf(pArgs->MetaFormat, meta.Version, meta.Size, meta.Count);
    printf("\n");

    int c = 0;
    for (int i = 0; i < meta.Count; i++)
    {
        Archipelago archipelago;
        ReadArchipelago(fd, &meta, &archipelago, i);

        bool condOrIsNameGiven =
                pArgs->IsNameGiven &&
                strcmp(archipelago.Name, pArgs->Name) == 0;
        bool condOrIsCountIslandsGiven =
                pArgs->IsCountIslandsGiven &&
                archipelago.CountIslands == pArgs->CountIslands;
        bool condOrIsCountInhabitedIslandsGiven =
                pArgs->IsCountInhabitedIslandsGiven &&
                archipelago.CountInhabitedIslands ==
                pArgs->CountInhabitedIslands;

        bool condAndIsNameGiven =
                (pArgs->IsNameGiven &&
                 strcmp(archipelago.Name, pArgs->Name) == 0) ||
                !pArgs->IsNameGiven;
        bool condAndIsCountIslandsGiven =
                (pArgs->IsCountIslandsGiven &&
                 archipelago.CountIslands == pArgs->CountIslands) ||
                !pArgs->IsCountIslandsGiven;
        bool condAndIsCountInhabitedIslandsGiven =
                (pArgs->IsCountInhabitedIslandsGiven &&
                 archipelago.CountInhabitedIslands ==
                 pArgs->CountInhabitedIslands) ||
                !pArgs->IsCountInhabitedIslandsGiven;

        if (pArgs->IsOr
            ? condOrIsNameGiven ||
              condOrIsCountIslandsGiven ||
              condOrIsCountInhabitedIslandsGiven
            : condAndIsNameGiven &&
              condAndIsCountIslandsGiven &&
              condAndIsCountInhabitedIslandsGiven)
        {
            printf(pArgs->Format,
                   archipelago.Name,
                   archipelago.CountIslands,
                   archipelago.CountInhabitedIslands);
            printf("\n");
            c++;
        }
    }

    printf(pArgs->CountFormat, c);
    printf("\n");

    if (pArgs->IsHexDumpRequired)
    {
        HexDump(fd);
    }

    CloseFile1(fd);
}

void HexdumpExec(Args* pArgs)
{
    int fd = pArgs->IsForceCreate
             ? CreateFile1(pArgs->FileName, sizeof(Archipelago))
             : OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));

    HexDump(fd);

    CloseFile1(fd);
}

void HelpExec(Args* pArgs)
{
    printf("справка\n");
}

void UnknownOptionExec(Args* pArgs)
{
    printf("Неизвестный параметр: %c\n", pArgs->UnknownOption);
}

int Exec(char* command, Args* pArgs)
{
    if (pArgs->IsHelpGiven ||
        strcmp(command, HELP_COMMAND_NAME) == 0 ||
        strcmp(command, HELP_OPT_NAME) == 0)
    {
        HelpExec(pArgs);
    }
    else if (pArgs->IsUnknownOptionGiven)
    {
        UnknownOptionExec(pArgs);
    }
    else if (strcmp(command, ADD_COMMAND_NAME) == 0)
    {
        AddCommandExec(pArgs);
    }
    else if (strcmp(command, MODIFY_COMMAND_NAME) == 0)
    {
        ModifyCommandExec(pArgs);
    }
    else if (strcmp(command, REMOVE_COMMAND_NAME) == 0)
    {
        RemoveCommandExec(pArgs);
    }
    else if (strcmp(command, DELETE_COMMAND_NAME) == 0)
    {
        DeleteCommandExec(pArgs);
    }
    else if (strcmp(command, HAS_UNINHABITED_COMMAND_NAME) == 0)
    {
        HasUninhabitedCommandExec(pArgs);
    }
    else if (strcmp(command, PRINT_COMMAND_NAME) == 0)
    {
        PrintCommandExec(pArgs);
    }
    else if (strcmp(command, HEXDUMP_COMMAND_NAME) == 0)
    {
        HexdumpExec(pArgs);
    }
    else
    {
        printf("Введена неверная команда\n");
        return 1;
    }
    return 0;
}
