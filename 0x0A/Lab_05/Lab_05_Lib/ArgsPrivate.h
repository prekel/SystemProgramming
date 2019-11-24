/// \file
/// \brief Константы и функции общие для аргументов командной строки клиента и сервера
/// \details Константы и функции общие для аргументов командной строки клиента и сервера.

#ifndef ARGSPRIVATE_H
#define ARGSPRIVATE_H

#include "Args.h"
#include "Utils.h"

#define DEFAULT_IP_ADDRESS "127.0.0.1"
#define DEFAULT_PORT 20522

#define OPT_PORT 'p'
#define OPT_PORT_USAGE "-p целое"
#define OPT_PORT_DESCRIPTION "Порт. По умолчанию " STRINGIZE(DEFAULT_PORT) "."
#define OPT_HELP 'h'
#define OPT_HELP_USAGE "-h"
#define OPT_HELP_DESCRIPTION "Требуется ли вывод справки."
#define OPT_UNKNOWN '?'

#define HELP_SEP ": "
#define HELP_SUFFIX "\n"

/// Выводит сообщение о неизвестной параметре.
///
/// \param unknownOption Неизвестный параметр.
void UnknownOptionInternal(char unknownOption);

#endif //ARGSPRIVATE_H
