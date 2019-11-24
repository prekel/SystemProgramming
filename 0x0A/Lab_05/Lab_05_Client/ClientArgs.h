/// \file
/// \brief Аргументы коммандной строки клиента
/// \details Аргументы коммандной строки и их парсинг.

#ifndef CLIENTARGS_H
#define CLIENTARGS_H

#include <stdbool.h>

#include "Args.h"

#include "Matrix.h"

/// \struct Args
///
/// Аргументы коммандной строки.
struct Args
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
};

/// Считывает из стандарного ввода недостающие опции.
///
/// \param pArgs Указатель на аргументы командной строки.
/// \return SUCCESSFUL (0) в случае успеха.
int InputAllOption(Args* pArgs);

/// Считывает матрицу из стандарного ввода, если не была задана в аргументах
/// командной строки.
///
/// \param pArgs Указатель на аргументы командной строки.
/// \param pMatrixA Указатель на матрицу A.
/// \param pMatrixB Указатель на матрицу B.
/// \return SUCCESSFUL (0) в случае успеха, BAD_ARGS или BAD_VALUE в случае
/// ошибки.
int InputOrFillMatrices(Args* pArgs, Matrix* pMatrixA, Matrix* pMatrixB);

#endif //CLIENTARGS_H
