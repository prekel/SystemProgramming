/// \file
/// \brief Коды возврата функций приложения.
/// \details Коды возврата функций приложения, сообщения для вывода сообщений
/// об ошибках.

#ifndef RETURNCODES_H
#define RETURNCODES_H

#include "ReturnCodes.h"


#define BAD_ARGS_MESSAGE "Указаны неверные параметры, введите параметр -h для вывода справки\n"

#define BAD_ARGS (-4)


#define UNKNOWN_ERROR_MESSAGE "Неизвестная ошибка\n"

#define WRONG_COMMAND_MESSAGE "Введена неверная команда, введите параметр -h для вывода справки\n"

#define NO_COMMAND_MESSAGE "Не введена команда, введите параметр -h для вывода справки\n"


#endif //RETURNCODES_H
