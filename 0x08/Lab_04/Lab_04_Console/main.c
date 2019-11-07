/// \file
/// \brief Главная функция программы
/// \details Главная функция программы.

#ifdef _MSC_VER
#include <Windows.h>
#elif _WIN32
#include <windows.h>
#endif

#include "Print.h"
#include "Commands.h"

/// Главная функция программы.
///
/// \param argc Кол-во аргументов.
/// \param argv Массив аргументов.
/// \return EXIT_SUCCESS (0) в случае успешного завершения программы,
/// EXIT_FAILURE в случае какой-либо ошибки.
int main(int argc, char** argv)
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    char* command = argv[1];
    Args* pArgs = ParseArgs(argc - 1, argv + 1);

    int ret = Exec(command, pArgs);

    DestroyArgs(pArgs);

    return ret;
}
