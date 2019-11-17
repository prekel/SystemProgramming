/// \file
/// \brief Коды возврата функций в библиотеке.
/// \details Коды возврата функций в библиотеке, сообщения для вывода
/// сообщений об ошибках и макросы для возвращения значений из функций.

#ifndef RETURNCODES_H
#define RETURNCODESLIB_H

#include <stddef.h>

/// Код возврата успешного завершения функции.
#define SUCCESSFUL 0

/// Сообщение при неудачной файловой операции
#define UNSUCCESSFUL_MESSAGE "Не удалось открыть/прочитать/записать файл\n"
/// Код возврата функции при неудачной файловой операции
#define UNSUCCESSFUL (-1)

/// Сообщение при введённом неверном значении
#define BAD_VALUE_MESSAGE "Введено неверное значение\n"
/// Код возврата при введённом неверном значении
#define BAD_VALUE (-2)

///// Сообщение при не найденом элементе
//#define NOT_FOUND_MESSAGE "Не найдено\n"
///// Код возврата при не найденом элементе
//#define NOT_FOUND (-3)

#define BAD_ARGS_MESSAGE "Указаны неверные параметры, введите параметр -h для вывода справки\n"

#define BAD_ARGS (-4)

///// Сообщение при несуществующем файле
//#define FILE_NOT_EXIST_MESSAGE "Файл не существует\n"
///// Код возврата при несуществующем файле
//#define FILE_NOT_EXIST (-5)

///// Сообщение при неудачном закрытии файла
//#define CLOSE_UNSUCCESSFUL_MESSAGE "Не удалось закрыть файл\n"
///// Код возврата при неудачном закрытии файла
//#define CLOSE_UNSUCCESSFUL (-6)
//
///// Сообщение при неправильном формате файла
//#define BAD_META_MESSAGE "Неправильный формат файла\n"
///// Код возврата при неправильном формате файла
//#define BAD_META (-7)
//
///// Сообщение при неправильной аписи в файле
//#define BAD_RECORD_MESSAGE "Неправильная запись в файле\n"
///// Код возврата при неправильной аписи в файле
//#define BAD_RECORD (-8)

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

/// Если f меньше нуля (то есть функция завершилась с неуспешным кодом
/// возврата), то функция, в которой используется макрос вернёт то,
/// чему равно f.
///
/// \param f Проверяемое целое число или выражение, возвращающее целое число
#define RETURN_IF_NOT_NULL(f) do { \
    int tmp = (f); \
    if (tmp != SUCCESSFUL) \
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

char* ReturnCodeLibMessage(int returnCode);

#endif //RETURNCODES_H
