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

    Archipelago a1 = {"a1rchipelago22222222222222222222222222222221", 12, 3};
    Archipelago a2 = {"a1rchipel3123421423432453rfwesfgredashgedrsahgreago2", 11, 0};

    char* path = "1.bin";

    int fd = OpenOrCreateFile(path, sizeof(Archipelago)); HexDump(fd);

    AddRecord(fd, &a1); HexDump(fd);
    AddRecord(fd, &a2); HexDump(fd);

    //RemoveSwapWithLast(fd, 0, 0); HexDump(fd);

    CloseFile(fd);

    return 0;
}
