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
#include "Print.h"
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
    Args* pArgs = ParseArgs(argc - 1, argv + 1);

    int ret = Exec(command, pArgs);

    DestroyArgs(pArgs);

    return ret;
}
