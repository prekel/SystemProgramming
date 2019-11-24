/// \file
/// \brief Аргументы коммандной строки клиента
/// \details Аргументы коммандной строки и их парсинг.

#ifndef CLIENT_ARGS_H
#define CLIENT_ARGS_H

#include <stdbool.h>

#include "Matrix.h"

/// \struct Args
///
/// Аргументы коммандной строки.
typedef struct
{
    /// Дан ли IP-адрес сервера.
    bool IsIpAddressGiven;
    /// IP-адрес сервера.
    char* IpAddress;

    /// Дан ли порт.
    bool IsPortGiven;
    /// Порт.
    int Port;

    /// Дана ли степень матрицы.
    bool IsDegreeGiven;
    /// Степень матрицы.
    int Degree;

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
} Args;

/// Создаёт аргументы командной строки, инициализируя значениями по умолчанию.
/// Требуется очистка с помощью DestroyArgs().
///
/// \return Указатель на аргументы коммандной строки. NULL в случае ошибки
/// аллокации.
Args* CreateArgs();

/// Уничтожает аргументы командной строки.
///
/// \param pArgs Указатель на аргументы коммандной строки.
void DestroyArgs(Args* pArgs);

/// Парсит аргументы командкой строки. Требуется очистка с
/// помощью DestroyArgs().
///
/// \param argc Кол-во аргументов в массиве (без последнего NULL-элемента).
/// \param pArgv Массив аргументов, начинающийся на название комманды и
/// заканчивающийся NULL-элементом.
/// \return Указатель на аргументы коммандной строки. NULL в случае ошибки
/// аллокации.
Args* ParseArgs(int argc, char** pArgv);

/// Считывает из стандарного ввода недостающие опции.
///
/// \param pArgs Указатель на аргументы командной строки.
/// \return SUCCESSFUL (0) в случае успеха.
int InputAllOption(Args* pArgs);

/// Считывает матрицу из стандарного ввода, если не была задана в аргументах
/// командной строки.
///
/// \param pArgs Указатель на аргументы командной строки.
/// \param pMatrixA Указатель на матрицу.
/// \return SUCCESSFUL (0) в случае успеха, BAD_ARGS или BAD_VALUE в случае
/// ошибки.
int InputOrFillMatrices(Args* pArgs, Matrix* pMatrixA, Matrix* pMatrixB);

/// Выводит справку.
void PrintHelp();

/// Действие при неизвестном параметре.
///
/// \param pArgs
void UnknownOption(Args* pArgs);

#endif //CLIENT_ARGS_H
