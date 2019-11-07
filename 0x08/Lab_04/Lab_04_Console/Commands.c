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
        return BAD_VALUE;
    }

    Meta meta;
    int readMeta = ReadMeta(fd, &meta);
    if (readMeta == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    if (AddArchipelago(fd, &meta, &archipelago) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    return SUCCESSFUL;
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

    return SUCCESSFUL;
}

int RemoveCommandExec(int fd, Args* pArgs)
{
    if (!(pArgs->IsIndexGiven || pArgs->IsNameGiven) ||
        (pArgs->IsIndexGiven && pArgs->IsNameGiven) ||
        (pArgs->IsIndexGiven && pArgs->Index >= 0))
    {
        return BAD_VALUE;
    }

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

    return SUCCESSFUL;
}

int DeleteCommandExec(int fd, Args* pArgs)
{
    bool isExist = IsExist(pArgs->FileName);
    if (isExist == false)
    {
        return FILE_NOT_EXIST;
    }

    if (DeleteFile(pArgs->FileName) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    return SUCCESSFUL;
}

int HasUninhabitedCommandExec(int fd, Args* pArgs)
{
    if (!(pArgs->IsIndexGiven || pArgs->IsOldNameGiven) ||
        (pArgs->IsIndexGiven && pArgs->IsOldNameGiven))
    {
        return BAD_ARGS;
    }

    Meta meta;
    int readMeta = ReadMeta(fd, &meta);
    if (readMeta == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

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

    return SUCCESSFUL;
}

int PrintCommandExec(int fd, Args* pArgs)
{
    Print(fd, pArgs, false);

    return SUCCESSFUL;
}

int HexdumpCommandExec(int fd, Args* pArgs)
{
    if (pArgs->IsPrintRequired)
    {
        Print(fd, pArgs, true);
    }

    HexDump(fd);

    return SUCCESSFUL;
}

int HelpCommandExec(int fd, Args* pArgs)
{
    printf("справка\n");
    return SUCCESSFUL;
}

int UnknownOptionCommandExec(int fd, Args* pArgs)
{
    printf("Неизвестный параметр: %c\n", pArgs->UnknownOption);
    return SUCCESSFUL;
}

#define FILE_UNSUCCESSFUL_MESSAGE "Не удалось открыть/прочитать/записать файл\n"

#define BAD_VALUE_MESSAGE "Введено неверное значение\n"

#define NOT_FOUND_MESSAGE "Не найдено\n"

#define BAD_ARGS_MESSAGE "Указаны неверные параметры\n"

#define FILE_NOT_EXIST_MESSAGE "Файл не существует\n"

#define CLOSE_UNSUCCESSFUL_MESSAGE "Не удалось закрыть файл\n"

#define UNKNOWN_ERROR_MESSAGE "Неизвестная ошибка\n"

#define WRONG_COMMAND_MESSAGE "Введена неверная команда\n"

#define NO_COMMAND_MESSAGE "Не введена команда\n"

int Exec(char* command, Args* pArgs)
{
    int (* commandExec)(int, Args*);
    bool isFileRequired = false;

    if (command == NULL || command[0] == '\0')
    {
        printf(NO_COMMAND_MESSAGE);
        return EXIT_FAILURE;
    }
    else if (pArgs->IsHelpGiven ||
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
        printf(WRONG_COMMAND_MESSAGE);
        return EXIT_FAILURE;
    }
    
    int ret = Exec1(pArgs, commandExec, isFileRequired);

    switch (ret)
    {
    case SUCCESSFUL:
        return EXIT_SUCCESS;
    case FILE_UNSUCCESSFUL:
        printf(FILE_UNSUCCESSFUL_MESSAGE);
    case BAD_VALUE:
        printf(BAD_VALUE_MESSAGE);
    case NOT_FOUND:
        printf(NOT_FOUND_MESSAGE);
    case BAD_ARGS:
        printf(BAD_ARGS_MESSAGE);
    case FILE_NOT_EXIST:
        printf(FILE_NOT_EXIST_MESSAGE);
    case CLOSE_UNSUCCESSFUL:
        printf(CLOSE_UNSUCCESSFUL_MESSAGE);
    default:
        printf(UNKNOWN_ERROR_MESSAGE);
    }

    return EXIT_FAILURE;
}

int Exec1(Args* pArgs, int (* commandExec)(int, Args*), bool isFileRequired)
{
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

    int commendExecRet = commandExec(fd, pArgs);
    if (commendExecRet < 0)
    {
        return commendExecRet;
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

    if (CloseFile1(fd))
    {
        return CLOSE_UNSUCCESSFUL;
    }

    return SUCCESSFUL;
}
