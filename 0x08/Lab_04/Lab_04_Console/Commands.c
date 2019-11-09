/// \file
/// \brief Реализация функций из Commands.h
/// \details Реализация функций из Commands.h.

#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Archipelago.h"
#include "Commands.h"
#include "RecordFile.h"
#include "Print.h"
#include "ParseInt.h"
#include "ReturnCodes.h"
#include "ReturnCodesLib.h"

#define EXTRA_ARGS_NAME_INDEX 0
#define EXTRA_ARGS_COUNT_ISLANDS_INDEX 1
#define EXTRA_ARGS_COUNT_INHABITED_ISLANDS_INDEX 2

#define ARCHIPELAGO_INT_ARGS_COUNT 2

int AddCommand(int fd, Args* pArgs)
{
    Archipelago archipelago;

    if (pArgs->IsNameGiven && pArgs->IsCountIslandsGiven &&
        pArgs->IsCountInhabitedIslandsGiven)
    {
        RETURN_IF_NOT_SUCCESSFUL(
                FillArchipelago(&archipelago,
                                pArgs->Name,
                                pArgs->CountIslands,
                                pArgs->CountInhabitedIslands));
    }
    else
    {
        char* name =
                pArgs->pExtraArgs[EXTRA_ARGS_NAME_INDEX];
        char* countIslandsString =
                pArgs->pExtraArgs[EXTRA_ARGS_COUNT_ISLANDS_INDEX];
        char* countInhabitedIslandsString =
                pArgs->pExtraArgs[EXTRA_ARGS_COUNT_INHABITED_ISLANDS_INDEX];

        if (name == NULL ||
            countIslandsString == NULL ||
            countInhabitedIslandsString == NULL)
        {
            return BAD_ARGS;
        }

        int successfulCount = 0;
        int fill = FillArchipelago(&archipelago,
                                   name,
                                   ParseInt(countIslandsString,
                                            &successfulCount),
                                   ParseInt(countInhabitedIslandsString,
                                            &successfulCount));

        if (successfulCount < ARCHIPELAGO_INT_ARGS_COUNT || fill < SUCCESSFUL)
        {
            return fill;
        }
    }

    Meta meta;
    RETURN_IF_NOT_SUCCESSFUL(ReadMeta(fd, &meta));

    RETURN_IF_NOT_SUCCESSFUL(AddArchipelago(fd, &meta, &archipelago));

    return SUCCESSFUL;
}

int ModifyCommand(int fd, Args* pArgs)
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
    RETURN_IF_NOT_SUCCESSFUL(ReadMeta(fd, &meta));

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
        RETURN_IF_NOT_SUCCESSFUL(ModifyName(fd, &meta, index, pArgs->Name));

    }
    if (pArgs->IsCountIslandsGiven)
    {
        RETURN_IF_NOT_SUCCESSFUL(ModifyCountIslands(fd, &meta, index,
                                                    pArgs->CountIslands));
    }
    if (pArgs->IsCountInhabitedIslandsGiven)
    {
        RETURN_IF_NOT_SUCCESSFUL(
                ModifyCountInhabitedIslands(fd,
                                            &meta,
                                            index,
                                            pArgs->CountInhabitedIslands));
    }

    return SUCCESSFUL;
}

int RemoveCommand(int fd, Args* pArgs)
{
    if (!(pArgs->IsIndexGiven || pArgs->IsNameGiven) &&
        (pArgs->IsIndexGiven && pArgs->IsNameGiven) &&
        (pArgs->IsIndexGiven && pArgs->Index >= 0))
    {
        return BAD_VALUE;
    }

    Meta meta;
    RETURN_IF_NOT_SUCCESSFUL(ReadMeta(fd, &meta));

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
        RETURN_IF_NOT_SUCCESSFUL(RemoveRecordSwapWithLast(fd, &meta, index));
    }
    else
    {
        RETURN_IF_NOT_SUCCESSFUL(RemoveRecordShift(fd, &meta, index));
    }

    return SUCCESSFUL;
}

int CreateCommand(int fd, Args* pArgs)
{
    if (fd == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return SUCCESSFUL;
}

int DeleteCommand(int fd, Args* pArgs)
{
    bool isExist = IsExistWritableReadableRecordFile(pArgs->FilePath);
    if (isExist == false)
    {
        return FILE_NOT_EXIST;
    }

    RETURN_IF_NOT_SUCCESSFUL(DeleteRecordFile(pArgs->FilePath));

    return SUCCESSFUL;
}

#define HAS_UNINHABITED_EXIST "Имеются архипелаги, состоящие только из необитаемых островов\n"

#define HAS_UNINHABITED_NOT_EXIST "Отсутствуют архипелаги, состоящие только из необитаемых островов\n"

int HasUninhabitedCommand(int fd, Args* pArgs)
{
    Meta meta;
    RETURN_IF_NOT_SUCCESSFUL(ReadMeta(fd, &meta));

    bool has = false;
    for (int i = 0; i < meta.Count; i++)
    {
        Archipelago archipelago;
        RETURN_IF_NOT_SUCCESSFUL(ReadArchipelago(fd, &meta, &archipelago, i));
        RETURN_IF_NOT_SUCCESSFUL(VerifyArchipelago(&archipelago));
        if (archipelago.CountInhabitedIslands == 0)
        {
            has = true;
            break;
        }
    }

    if (has)
    {
        printf(HAS_UNINHABITED_EXIST);
    }
    else
    {
        printf(HAS_UNINHABITED_NOT_EXIST);
    }

    return SUCCESSFUL;
}

int PrintCommand(int fd, Args* pArgs)
{
    RETURN_IF_NOT_SUCCESSFUL(Print(fd, pArgs, false));

    return SUCCESSFUL;
}

int HexdumpCommand(int fd, Args* pArgs)
{
    RETURN_IF_NOT_SUCCESSFUL(HexDump(fd));

    return SUCCESSFUL;
}

#define HELP_MESSAGE "справка\n"

int HelpCommand(int fd, Args* pArgs)
{
    printf(HELP_MESSAGE);
    return SUCCESSFUL;
}

#define UNKNOWN_OPT_MESSAGE "Неизвестный параметр: %c\n"

int UnknownOptionCommand(int fd, Args* pArgs)
{
    if (pArgs->UnknownOption == '\0' ||
        pArgs->CountValidArgs < pArgs->CountArgs)
    {
        return BAD_ARGS;
    }
    else
    {
        printf(UNKNOWN_OPT_MESSAGE, pArgs->UnknownOption);
    }
    return SUCCESSFUL;
}

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
        commandExec = HelpCommand;
    }
    else if (pArgs->IsUnknownOptionGiven ||
             pArgs->CountValidArgs < pArgs->CountArgs)
    {
        commandExec = UnknownOptionCommand;
    }
    else if (strcmp(command, ADD_COMMAND_NAME) == 0)
    {
        isFileRequired = true;
        commandExec = AddCommand;
    }
    else if (strcmp(command, MODIFY_COMMAND_NAME) == 0)
    {
        isFileRequired = true;
        commandExec = ModifyCommand;
    }
    else if (strcmp(command, REMOVE_COMMAND_NAME) == 0)
    {
        isFileRequired = true;
        commandExec = RemoveCommand;
    }
    else if (strcmp(command, DELETE_COMMAND_NAME) == 0)
    {
        commandExec = DeleteCommand;
    }
    else if (strcmp(command, CREATE_COMMAND_NAME) == 0)
    {
        isFileRequired = true;
        commandExec = CreateCommand;
    }
    else if (strcmp(command, HAS_UNINHABITED_COMMAND_NAME) == 0)
    {
        isFileRequired = true;
        commandExec = HasUninhabitedCommand;
    }
    else if (strcmp(command, PRINT_COMMAND_NAME) == 0)
    {
        isFileRequired = true;
        commandExec = PrintCommand;
    }
    else if (strcmp(command, HEXDUMP_COMMAND_NAME) == 0)
    {
        isFileRequired = true;
        commandExec = HexdumpCommand;
    }
    else
    {
        printf(WRONG_COMMAND_MESSAGE);
        return EXIT_FAILURE;
    }

    int ret = CommandExec(pArgs, commandExec, isFileRequired);
    if (ret > SUCCESSFUL)
    {
        ret = SUCCESSFUL;
    }

    switch (ret)
    {
    case SUCCESSFUL:
        return EXIT_SUCCESS;
    case FILE_UNSUCCESSFUL:
        fprintf(stderr, FILE_UNSUCCESSFUL_MESSAGE);
        break;
    case BAD_VALUE:
        fprintf(stderr, BAD_VALUE_MESSAGE);
        break;
    case NOT_FOUND:
        fprintf(stderr, NOT_FOUND_MESSAGE);
        break;
    case BAD_ARGS:
        fprintf(stderr, BAD_ARGS_MESSAGE);
        break;
    case FILE_NOT_EXIST:
        fprintf(stderr, FILE_NOT_EXIST_MESSAGE);
        break;
    case CLOSE_UNSUCCESSFUL:
        fprintf(stderr, CLOSE_UNSUCCESSFUL_MESSAGE);
        break;
    case BAD_META:
        fprintf(stderr, BAD_META_MESSAGE);
        break;
    case BAD_RECORD:
        fprintf(stderr, BAD_RECORD_MESSAGE);
        break;
    case ALLOCATION_ERROR:
        fprintf(stderr, ALLOCATION_ERROR_MESSAGE);
        break;
    default:
        fprintf(stderr, UNKNOWN_ERROR_MESSAGE);
        break;
    }

    return EXIT_FAILURE;
}

int CommandExec(Args* pArgs, int (* commandExec)(int, Args*), bool isFileRequired)
{
    int fd;
    if (!isFileRequired)
    {
        fd = FILE_UNSUCCESSFUL;
    }
    else if (pArgs->IsOpenOrCreate || commandExec == CreateCommand)
    {
        fd = OpenOrCreateRecordFile(pArgs->FilePath, sizeof(Archipelago));
    }
    else if (pArgs->IsReCreate)
    {
        fd = CreateOrTruncateRecordFile(pArgs->FilePath, sizeof(Archipelago));
    }
    else
    {
        if (!IsExistWritableReadableRecordFile(pArgs->FilePath))
        {
            return FILE_NOT_EXIST;
        }
        fd = OpenRecordFile(pArgs->FilePath);
    }

    if (isFileRequired)
    {
        RETURN_IF_NOT_SUCCESSFUL(CheckRecordFile(fd, sizeof(Archipelago)));
    }

    int ret = commandExec(fd, pArgs);
    RETURN_IF_NOT_SUCCESSFUL(ret);

    if (pArgs->IsPrintRequired)
    {
        RETURN_IF_NOT_SUCCESSFUL(Print(fd, pArgs, true));
    }

    if (pArgs->IsHexDumpRequired)
    {
        RETURN_IF_NOT_SUCCESSFUL(HexDump(fd));
    }

    if (isFileRequired && CloseRecordFile(fd) == FILE_UNSUCCESSFUL)
    {
        return CLOSE_UNSUCCESSFUL;
    }

    return ret;
}
