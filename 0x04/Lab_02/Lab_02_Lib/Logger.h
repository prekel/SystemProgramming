/// \file
/// \brief Функции и макросы для логгирования
/// \details Функции и макросы для логгирования.

#ifndef LOGGER_H
#define LOGGER_H

#include <time.h>
#include <string.h>

#include "Fork.h"
#include "Table.h"
#include "Philosopher.h"
#include "Utils.h"

/// Ширина в логе для имени файла
#define LOG_FILE_WIDTH 32
/// Формат аргументов для логгера генерируемых макросом
#define LOG_FMT "[%*s:%d] "
/// Перевод строки
#define LOG_NEWLINE "\n"
/// Аргументы для логгера генерируемые макросом
#define LOG_ARGS (LOG_FILE_WIDTH - sizeof(STRINGIZE(__LINE__))), _FILE, __LINE__
/// Помощник для макроса-логгера
#define LOG_HELPER(format, ...) Log(LOG_FMT format LOG_NEWLINE, __VA_ARGS__)

/// Логгирует сообщение с соответствующим форматом. Будет выведена информация
/// о столе (если не выключена), идентификатор потока, имя файла со строкой
/// и сообщение
///
/// \param message Сообщение (формат) для логгирования.
/// \param args Аргументы для вывода.
#define LOG(message, args...) LOG_HELPER(message, LOG_ARGS, ## args)

/// Инициализирует логгер.
///
/// \param pTable Стол.
/// \param pOutputStream1st Основной поток для вывода логов.
/// Например stdout или NULL.
/// \param isMainTableInfoEnabled Треуется ли выводить информацию о столе
/// в оснойной поток.
/// \param pOutputStream2nd Дополнительный поток для вывода логов.
/// Например fopen("1.log", "w+") или NULL.
/// \param isTableInfoEnabled Треуется ли выводить информацию о столе
/// в дополнительный поток.
void
InitLogger(Table* pTable, bool isTableInfoEnabled, FILE* pOutputStream1st,
           FILE* pOutputStream2nd, int (* pOutputFunction3th)(char*),
           int (* pOutputFunction4th)(char*));

/// Логгирует сообщение, рекомендуется использовать макрос
/// LOG(message, args...).
///
/// \param format Сообщение (формат) для логгирования.
/// \param ... Аргументы для вывода.
void Log(char* format, ...);

#endif //LOGGER_H
