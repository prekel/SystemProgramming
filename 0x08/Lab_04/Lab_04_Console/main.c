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

    char* command = argv[1];

    if (strcmp(command, ADD_COMMAND_NAME) == 0)
    {
        AddCommandExec(argc - 1, argv + 1);
        return 0;
    }
    if (strcmp(command, FORMAT_COMMAND_NAME) == 0)
    {
        FormatCommandExec(argc - 1, argv + 1);
        return 0;
    }


    Archipelago a1;
    FillArchipelago(&a1, "daswd", 12, 3);
    Archipelago a2;
    FillArchipelago(&a2, "wqde2", 11, 0);

    char* path = "2.bin";

    int fd = OpenOrCreateFile(path, sizeof(Archipelago));
    HexDump(fd);

    AddRecord(fd, &a1);
    HexDump(fd);
    AddRecord(fd, &a2);
    HexDump(fd);

    RemoveSwapWithLast(fd, 0, 1);
    HexDump(fd);

    CloseFile(fd);

    return 1;
}
