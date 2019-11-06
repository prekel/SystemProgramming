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
#include "Print.h"
#include "Utils.h"

int AddCommandExec(int fd, Args* pArgs)
{
    //int fd = pArgs->IsForceCreate
    //         ? CreateFile1(pArgs->FileName, sizeof(Archipelago))
    //         : OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));

    //if (fd == FILE_UNSUCCESSFUL)
    //{
    //    //printf("Не удалось открыть или создать файл");
    //    return FILE_UNSUCCESSFUL;
    //}

    Archipelago archipelago;
    if (!FillArchipelago(&archipelago,
                         pArgs->IsNameGiven
                         ? pArgs->Name
                         : pArgs->pExtraArgs[0],
                         pArgs->IsCountIslandsGiven
                         ? pArgs->CountIslands
                         : ParseInt(pArgs->pExtraArgs[1]),
                         pArgs->IsCountInhabitedIslandsGiven
                         ? pArgs->CountInhabitedIslands
                         : ParseInt(pArgs->pExtraArgs[2])))
    {
        //printf("Неверное знаение\n");
        return BAD_VALUE;
    }

    Meta meta;
    int readMeta = ReadMeta(fd, &meta);
    if (readMeta == FILE_UNSUCCESSFUL)
    {
        //printf("Не удалось открыть или создать файл\n");
        return FILE_UNSUCCESSFUL;
    }

    if (AddArchipelago(fd, &meta, &archipelago) == FILE_UNSUCCESSFUL)
    {
        //printf("Не удалось записать в файл\n");
        return FILE_UNSUCCESSFUL;
    }

    if (pArgs->IsPrintRequired)
    {
        int print = Print(fd, pArgs, true);
        if (print < 0)
        {
            return print;
        }
    }

    if (pArgs->IsHexDumpRequired)
    {
        int hexDump = HexDump(fd);
        if (hexDump < 0)
        {
            return hexDump;
        }
    }

    if (CloseFile1(fd) == FILE_UNSUCCESSFUL)
    {
        return CLOSE_UNSUCCESSFUL;
    }

    return 0;
}

int ModifyCommandExec(int fd, Args* pArgs)
{
    if (!((pArgs->IsIndexGiven || pArgs->IsOldNameGiven) &&
          !(pArgs->IsIndexGiven && pArgs->IsOldNameGiven)) &&
        (pArgs->IsNameGiven || pArgs->IsCountIslandsGiven ||
         pArgs->IsCountInhabitedIslandsGiven) &&
        (pArgs->IsIndexGiven && pArgs->Index >= 0))
    {
        return BAD_ARGS;
    }

    int fd = pArgs->IsForceCreate
             ? CreateFile1(pArgs->FileName, sizeof(Archipelago))
             : OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));

    if (fd == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    Meta meta;
    int readMeta = ReadMeta(fd, &meta);
    if (readMeta == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    if (!(pArgs->IsIndexGiven && pArgs->Index < meta.Count))
    {
        return BAD_ARGS;
    }

    int index = pArgs->IsIndexGiven
                ? pArgs->Index
                : IndexByName(fd, &meta, pArgs->OldName);

    if (index == NOT_FOUND)
    {
        return NOT_FOUND;
    }

    if (pArgs->IsNameGiven)
    {
        int modifyName = ModifyName(fd, &meta, index, pArgs->Name);
        if (modifyName < 0)
        {
            return modifyName;
        }
    }
    if (pArgs->IsCountIslandsGiven)
    {
        int modifyCountIslands = ModifyCountIslands(fd, &meta, index,
                                                    pArgs->CountIslands);
        if (modifyCountIslands < 0)
        {
            return modifyCountIslands;
        }
    }
    if (pArgs->IsCountInhabitedIslandsGiven)
    {
        int modifyCountInhabitedIslands =
                ModifyCountInhabitedIslands(fd,
                                            &meta,
                                            index,
                                            pArgs->CountInhabitedIslands);
        if (modifyCountInhabitedIslands < 0)
        {
            return modifyCountInhabitedIslands;
        }
    }

    if (pArgs->IsPrintRequired)
    {
        Print(fd, pArgs, true);
    }

    if (pArgs->IsHexDumpRequired)
    {
        HexDump(fd);
    }

    if (CloseFile1(fd) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    return 0;
}

int RemoveCommandExec(int fd, Args* pArgs)
{
    assert(pArgs->IsIndexGiven || pArgs->IsNameGiven);
    assert(!(pArgs->IsIndexGiven && pArgs->IsNameGiven));
    assert(pArgs->IsIndexGiven && pArgs->Index >= 0);

    int fd = pArgs->IsForceCreate
             ? CreateFile1(pArgs->FileName, sizeof(Archipelago))
             : OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));

    if (fd == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    Meta meta;
    int readMeta = ReadMeta(fd, &meta);
    if (readMeta == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    if (!(pArgs->IsIndexGiven && pArgs->Index < meta.Count))
    {
        return BAD_ARGS;
    }

    int index = pArgs->IsIndexGiven
                ? pArgs->Index
                : IndexByName(fd, &meta, pArgs->Name);

    if (index == NOT_FOUND)
    {
        return NOT_FOUND;
    }

    if (pArgs->IsRemoveSwapWithLast)
    {
        int removeSwapWithLast = RemoveSwapWithLast(fd, &meta, index);
        if (removeSwapWithLast < 0)
        {
            return removeSwapWithLast;
        }
    }
    else
    {
        int removeShift = RemoveShift(fd, &meta, index);
        if (removeShift < 0)
        {
            return removeShift;
        }
    }

    if (pArgs->IsPrintRequired)
    {
        int print = Print(fd, pArgs, true);
        if (print < 0)
        {
            return print;
        }
    }

    if (pArgs->IsHexDumpRequired)
    {
        int hexDump = HexDump(fd);
        if (hexDump < 0)
        {
            return hexDump;
        }
    }

    if (CloseFile1(fd) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    return 0;
}

int DeleteCommandExec(int fd, Args* pArgs)
{
    bool isExist = IsExist(pArgs->FileName);
    if (isExist == false)
    {
        return FILE_NOT_EXIST;
    }

    int deleteFile = DeleteFile(pArgs->FileName);
    assert(deleteFile == 0);
}

int HasUninhabitedCommandExec(int fd, Args* pArgs)
{
    assert(!pArgs->IsMetaFormatGiven);
    assert(!pArgs->IsFormatGiven);
    assert(pArgs->IsIndexGiven || pArgs->IsOldNameGiven);
    assert(!(pArgs->IsIndexGiven && pArgs->IsOldNameGiven));

    int fd = pArgs->IsForceCreate
             ? CreateFile1(pArgs->FileName, sizeof(Archipelago))
             : OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));

    if (fd == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    Meta meta;
    int readMeta = ReadMeta(fd, &meta);
    assert(readMeta != FILE_UNSUCCESSFUL);

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

    if (pArgs->IsPrintRequired)
    {
        Print(fd, pArgs, true);
    }

    if (pArgs->IsHexDumpRequired)
    {
        HexDump(fd);
    }

    CloseFile1(fd);
}

int PrintCommandExec(int fd, Args* pArgs)
{
    int fd = pArgs->IsForceCreate
             ? CreateFile1(pArgs->FileName, sizeof(Archipelago))
             : OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));

    if (fd == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    Print(fd, pArgs, false);

    if (pArgs->IsPrintRequired)
    {
        Print(fd, pArgs, true);
    }

    if (pArgs->IsHexDumpRequired)
    {
        HexDump(fd);
    }

    CloseFile1(fd);
}

int HexdumpCommandExec(int fd, Args* pArgs)
{
    int fd = pArgs->IsForceCreate
             ? CreateFile1(pArgs->FileName, sizeof(Archipelago))
             : OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));

    if (pArgs->IsPrintRequired)
    {
        Print(fd, pArgs, true);
    }

    HexDump(fd);

    CloseFile1(fd);
}

int HelpCommandExec(int fd, Args* pArgs)
{
    printf("справка\n");
}

int UnknownOptionCommandExec(int fd, Args* pArgs)
{
    printf("Неизвестный параметр: %c\n", pArgs->UnknownOption);
}

int Exec(char* command, Args* pArgs)
{
    int (* commandExec)(int, Args*);
    bool isFileRequired = false;

    if (pArgs->IsHelpGiven ||
        strcmp(command, HELP_COMMAND_NAME) == 0 ||
        strcmp(command, HELP_OPT_NAME) == 0)
    {
        commandExec = HelpCommandExec;
    }
    else if (pArgs->IsUnknownOptionGiven)
    {
        commandExec = UnknownOptionCommandExec;
    }
    else if (strcmp(command, ADD_COMMAND_NAME) == 0)
    {
        isFileRequired = true;
        commandExec = AddCommandExec;
    }
    else if (strcmp(command, MODIFY_COMMAND_NAME) == 0)
    {
        isFileRequired = true;
        commandExec = ModifyCommandExec;
    }
    else if (strcmp(command, REMOVE_COMMAND_NAME) == 0)
    {
        isFileRequired = true;
        commandExec = RemoveCommandExec;
    }
    else if (strcmp(command, DELETE_COMMAND_NAME) == 0)
    {
        commandExec = DeleteCommandExec;
    }
    else if (strcmp(command, HAS_UNINHABITED_COMMAND_NAME) == 0)
    {
        isFileRequired = true;
        commandExec = HasUninhabitedCommandExec;
    }
    else if (strcmp(command, PRINT_COMMAND_NAME) == 0)
    {
        isFileRequired = true;
        commandExec = PrintCommandExec;
    }
    else if (strcmp(command, HEXDUMP_COMMAND_NAME) == 0)
    {
        isFileRequired = true;
        commandExec = HexdumpCommandExec;
    }
    else
    {
        printf("Введена неверная команда\n");
        return 1;
    }


    int fd;
    if (!isFileRequired)
    {
        fd = FILE_UNSUCCESSFUL;
    }
    else if (pArgs->IsForceCreate)
    {
        fd = CreateFile1(pArgs->FileName, sizeof(Archipelago));
    }
    else
    {
        fd = OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));
    }

    commandExec(fd, pArgs);



    return 0;
}
