/// \file
/// \brief Коды возврата функций.
/// \details Коды возврата функций, сообщения для вывода
/// сообщений об ошибках и макросы для возвращения значений из функций.

#ifndef RETURNCODES_H
#define RETURNCODES_H

#include <stddef.h>

/// Код возврата успешного завершения функции.
#define SUCCESSFUL 0

/// Сообщение при неудачной файловой операции
#define UNSUCCESSFUL_MESSAGE "Ошибка\n"
/// Код возврата функции при неудачной файловой операции
#define UNSUCCESSFUL (-1)

/// Сообщение при введённом неверном значении
#define BAD_VALUE_MESSAGE "Введено неверное значение\n"
/// Код возврата при введённом неверном значении
#define BAD_VALUE (-2)

/// Сообщение при введённом неверном параметре
#define BAD_ARGS_MESSAGE "Указаны неверные параметры, введите параметр -h для вывода справки\n"
/// Код возврата при введённом неверном параметре
#define BAD_ARGS (-4)

/// Сообщение при ошибки аллокации
#define ALLOCATION_ERROR_MESSAGE "Не удалось выделить память\n"
/// Код возврата при ошибке аллокации
#define ALLOCATION_ERROR (-9)

/// Сообщение при неизвестной ошибке
#define UNKNOWN_ERROR_MESSAGE "Неизвестная ошибка\n"

/// Если f меньше нуля (то есть функция завершилась с неуспешным кодом
/// возврата), то функция, в которой используется макрос вернёт то,
/// чему равно f.
///
/// \param f Проверяемое целое число или выражение, возвращающее целое число
#define RETURN_IF_NOT_SUCCESSFUL(f) do { \
    int tmp = (f); \
    if (tmp < SUCCESSFUL) \
    { \
        return tmp; \
    } \
} while (0)

/// Если ptr равен NULL, то функция в которой используется макрос, вернёт NULL.
///
/// \param ptr Проверяемый указатель или выражение, возвращающее указатель
#define RETURN_NULL_IF_NULLPTR(ptr) do { \
    if ((ptr) == NULL) \
    { \
        return NULL; \
    } \
} while (0)

/// Возвращает сообщение кода возврата.
///
/// \param returnCode Код возврата.
/// \return Сообщение кода возврата.
char* ReturnCodeMessage(int returnCode);

/// Печатает сообщение кода возврата и сообщение последней ошибки с
/// помощью PrintLastErrorMessage().
///
/// \param returnCode Код возврата.
void PrintReturnCodeMessage(int returnCode);

#endif //RETURNCODES_H
