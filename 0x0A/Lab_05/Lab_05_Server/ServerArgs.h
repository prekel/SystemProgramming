/// \file
/// \brief Аргументы коммандной строки сервера
/// \details Аргументы коммандной строки и их парсинг.


#ifndef SERVER_ARGS_H
#define SERVER_ARGS_H

#include <stdbool.h>

#include "Args.h"

/// \struct Args
///
/// Аргументы коммандной строки.
struct Args
{
    /// Дан ли порт.
    bool IsPortGiven;
    /// Порт.
    int Port;

    /// Требуется ли вывод справки.
    bool IsHelpGiven;

    /// Дан ли неизвестный параметр.
    bool IsUnknownOptionGiven;
    /// Символ неизвестного параметра.
    char UnknownOption;

    /// Кол-во ргументов
    int CountArgs;
    /// Кол-во првильных аргументов (когда в значении требуется число и дано число итд.).
    int CountValidArgs;

    /// Указатель на дополнительные аргуенты после параметров.
    char** pExtraArgs;
};

/// Вывод справки.
void PrintHelp();

/// Действие при неизвестном параметре.
///
/// \param pArgs
void UnknownOption(Args* pArgs);

#endif //SERVER_ARGS_H
