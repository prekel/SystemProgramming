/// \file
/// \brief Главная функция программы
/// \details Главная функция программы.

#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#ifdef WIN32
#include <windows.h>
#endif

#include "Archipelago.h"
#include "File.h"
#include "Meta.h"
#include "HexDump.h"
#include "Commands.h"

/// Главная функция программы.
///
/// \param argc Кол-во аргументов.
/// \param argv Массив аргументов.
/// \return 0 в случае успешного завершения программы.
int main(int argc, char** argv)
{
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    if (argc <= 1)
    {
        printf("Не введена команда\n");
        return 1;
    }

    char* command = argv[1];
    Args* pArgs=ParseArgs(argc - 1, argv + 1);

    if (strcmp(command, ADD_COMMAND_NAME) == 0)
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
    else if (strcmp(command, HAS_UNINHABITED_COMMAND_NAME) == 0)
    {
        HasUninhabitedCommandExec(pArgs);
    }
    else if (strcmp(command, PRINT_COMMAND_NAME) == 0)
    {
        PrintCommandExec(pArgs);
    }
    else
    {
        printf("Введена неверная команда\n");
        DestroyArgs(pArgs);
        return 1;
    }

    DestroyArgs(pArgs);

    return 0;
}
