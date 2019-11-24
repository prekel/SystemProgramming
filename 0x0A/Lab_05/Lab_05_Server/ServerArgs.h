/// \file
/// \brief Аргументы коммандной строки сервера
/// \details Аргументы коммандной строки и их парсинг.


#ifndef SERVERARGS_H
#define SERVERARGS_H

#include <stdbool.h>

#include "Args.h"

/// \struct Args
///
/// Аргументы коммандной строки сервера.
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

#endif //SERVERARGS_H
