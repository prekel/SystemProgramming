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
#include "File.h"
#include "Print.h"
#include "Utils.h"
#include "Macro.h"

#define EXTRA_ARGS_NAME_INDEX 0
#define EXTRA_ARGS_COUNT_ISLANDS_INDEX 1
#define EXTRA_ARGS_COUNT_INHABITED_ISLANDS_INDEX 2

#define ARCHIPELAGO_INT_ARGS_COUNT 2

int AddCommandExec(int fd, Args* pArgs)
{
    Archipelago archipelago;

    if (pArgs->IsNameGiven && pArgs->IsCountIslandsGiven &&
        pArgs->IsCountInhabitedIslandsGiven)
    {
        RETURN_IF_NOT_SUCCESSFUL(FillArchipelago(&archipelago,
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
//    int readMeta = ReadMeta(fd, &meta);
//    if (readMeta == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }

    RETURN_IF_NOT_SUCCESSFUL(AddArchipelago(fd, &meta, &archipelago));
//    if (AddArchipelago(fd, &meta, &archipelago) == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }

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
    RETURN_IF_NOT_SUCCESSFUL(ReadMeta(fd, &meta));
//    int readMeta = ReadMeta(fd, &meta);
//    if (readMeta == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }

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
//        int modifyName = ModifyName(fd, &meta, index, pArgs->Name);
//        if (modifyName < 0)
//        {
//            return modifyName;
//        }
    }
    if (pArgs->IsCountIslandsGiven)
    {
        RETURN_IF_NOT_SUCCESSFUL(ModifyCountIslands(fd, &meta, index,
                                                    pArgs->CountIslands));
//        int modifyCountIslands = ModifyCountIslands(fd, &meta, index,
//                                                    pArgs->CountIslands);
//        if (modifyCountIslands < 0)
//        {
//            return modifyCountIslands;
//        }
    }
    if (pArgs->IsCountInhabitedIslandsGiven)
    {
        RETURN_IF_NOT_SUCCESSFUL(ModifyCountInhabitedIslands(fd,
                                                             &meta,
                                                             index,
                                                             pArgs->CountInhabitedIslands));
//        int modifyCountInhabitedIslands =
//                ModifyCountInhabitedIslands(fd,
//                                            &meta,
//                                            index,
//                                            pArgs->CountInhabitedIslands);
//        if (modifyCountInhabitedIslands < 0)
//        {
//            return modifyCountInhabitedIslands;
//        }
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

    Meta meta;
    RETURN_IF_NOT_SUCCESSFUL(ReadMeta(fd, &meta));
//    int readMeta = ReadMeta(fd, &meta);
//    if (readMeta == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }

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
        RETURN_IF_NOT_SUCCESSFUL(RemoveSwapWithLast(fd, &meta, index));
//        int removeSwapWithLast = RemoveSwapWithLast(fd, &meta, index);
//        if (removeSwapWithLast < 0)
//        {
//            return removeSwapWithLast;
//        }
    }
    else
    {
        RETURN_IF_NOT_SUCCESSFUL(RemoveSwapWithLast(fd, &meta, index));
//        int removeShift = RemoveShift(fd, &meta, index);
//        if (removeShift < 0)
//        {
//            return removeShift;
//        }
    }

    return SUCCESSFUL;
}

int CreateCommandExec(int fd, Args* pArgs)
{
    if (fd == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
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

    RETURN_IF_NOT_SUCCESSFUL(DeleteFile(pArgs->FileName));

    return SUCCESSFUL;
}

#define HAS_UNINHABITED_EXIST "Имеются архипелаги, состоящие только из необитаемых островов\n"

#define HAS_UNINHABITED_NOT_EXIST "Отсутствуют архипелаги, состоящие только из необитаемых островов\n"

int HasUninhabitedCommandExec(int fd, Args* pArgs)
{
    Meta meta;
    RETURN_IF_NOT_SUCCESSFUL(ReadMeta(fd, &meta));
//    int readMeta = ReadMeta(fd, &meta);
//    if (readMeta == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }

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

int PrintCommandExec(int fd, Args* pArgs)
{
    RETURN_IF_NOT_SUCCESSFUL(Print(fd, pArgs, false));

    return SUCCESSFUL;
}

int HexdumpCommandExec(int fd, Args* pArgs)
{
    RETURN_IF_NOT_SUCCESSFUL(HexDump(fd));

    return SUCCESSFUL;
}

#define HELP_MESSAGE "справка\n"

int HelpCommandExec(int fd, Args* pArgs)
{
    printf(HELP_MESSAGE);
    return SUCCESSFUL;
}

#define UNKNOWN_OPT_MESSAGE "Неизвестный параметр: %c\n"

int UnknownOptionCommandExec(int fd, Args* pArgs)
{
    if (pArgs->UnknownOption == '\0')
    {
        return(BAD_ARGS);
    }
    else
    {
        printf(UNKNOWN_OPT_MESSAGE, pArgs->UnknownOption);
    }
    return SUCCESSFUL;
}

#define FILE_UNSUCCESSFUL_MESSAGE "Не удалось открыть/прочитать/записать файл\n"

#define BAD_VALUE_MESSAGE "Введено неверное значение\n"

#define NOT_FOUND_MESSAGE "Не найдено\n"

#define BAD_ARGS_MESSAGE "Указаны неверные параметры\n"

#define FILE_NOT_EXIST_MESSAGE "Файл не существует\n"

#define CLOSE_UNSUCCESSFUL_MESSAGE "Не удалось закрыть файл\n"

#define BAD_META_MESSAGE "Неправильный формат файла\n"

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
    else if (strcmp(command, CREATE_COMMAND_NAME) == 0)
    {
        isFileRequired = true;
        commandExec = CreateCommandExec;
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
        break;
    case BAD_VALUE:
        printf(BAD_VALUE_MESSAGE);
        break;
    case NOT_FOUND:
        printf(NOT_FOUND_MESSAGE);
        break;
    case BAD_ARGS:
        printf(BAD_ARGS_MESSAGE);
        break;
    case FILE_NOT_EXIST:
        printf(FILE_NOT_EXIST_MESSAGE);
        break;
    case CLOSE_UNSUCCESSFUL:
        printf(CLOSE_UNSUCCESSFUL_MESSAGE);
        break;
    case BAD_META:
        printf(BAD_META_MESSAGE);
        break;
    default:
        printf(UNKNOWN_ERROR_MESSAGE);
        break;
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
    else if (pArgs->IsOpenOrCreate || commandExec == CreateCommandExec)
    {
        fd = OpenOrCreateFile(pArgs->FileName, sizeof(Archipelago));
    }
    else if (pArgs->IsReCreate)
    {
        fd = CreateOrTruncateFile(pArgs->FileName, sizeof(Archipelago));
    }
    else
    {
        if (!IsExist(pArgs->FileName))
        {
            return FILE_NOT_EXIST;
        }
        fd = OpenFile1(pArgs->FileName);
    }

    if (isFileRequired)
    {
        RETURN_IF_NOT_SUCCESSFUL(CheckFile(fd, sizeof(Archipelago)));
//        int checkMetaReturns = CheckFile(fd, sizeof(Archipelago));
//        if (checkMetaReturns < 0)
//        {
//            return checkMetaReturns;
//        }
    }

    RETURN_IF_NOT_SUCCESSFUL(commandExec(fd, pArgs));
//    int commendExecRet = commandExec(fd, pArgs);
//    if (commendExecRet < 0)
//    {
//        return commendExecRet;
//    }

    if (pArgs->IsPrintRequired)
    {
        RETURN_IF_NOT_SUCCESSFUL(Print(fd, pArgs, true));
//        int print = Print(fd, pArgs, true);
//        if (print < 0)
//        {
//            return print;
//        }
    }

    if (pArgs->IsHexDumpRequired)
    {
        RETURN_IF_NOT_SUCCESSFUL(HexDump(fd));
//        int hexDump = HexDump(fd);
//        if (hexDump < 0)
//        {
//            return hexDump;
//        }
    }

    if (isFileRequired && CloseFile1(fd) == FILE_UNSUCCESSFUL)
    {
        return CLOSE_UNSUCCESSFUL;
    }

    return SUCCESSFUL;
}
