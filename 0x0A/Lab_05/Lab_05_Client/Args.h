/// \file
/// \brief Аргументы коммандной строки
/// \details Аргументы коммандной строки и их парсинг.

#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>

#include "Matrix.h"

#define DEFAULT_IP_ADDRESS "127.0.0.1"
#define DEFAULT_PORT 20522

#define OPT_STRING ":a:p:n:f:s:"

#define OPT_IP_ADDRESS 'a'
#define OPT_IP_ADDRESS_USAGE "-a целое.целое.целое.целое"
#define OPT_IP_ADDRESS_DESCRIPTION "IP-адрес сервера."
#define OPT_PORT 'p'
#define OPT_PORT_USAGE "-p целое"
#define OPT_PORT_DESCRIPTION "Порт."
#define OPT_DEGREE 'n'
#define OPT_DEGREE_USAGE "-n целое"
#define OPT_DEGREE_DESCRIPTION "Степень матрицы."
#define OPT_FIRST_INDEX 'f'
#define OPT_FIRST_INDEX_USAGE "-f целое"
#define OPT_FIRST_INDEX_DESCRIPTION "Первый индекс."
#define OPT_SECOND_INDEX 's'
#define OPT_SECOND_INDEX_USAGE "-s целое"
#define OPT_SECOND_INDEX_DESCRIPTION "Второй индекс."
#define OPT_HELP 'h'
#define OPT_HELP_USAGE "-h"
#define OPT_HELP_DESCRIPTION "Требуется ли вывод справки."
#define OPT_UNKNOWN '?'

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

    /// Дан ли первый индекс.
    bool IsFirstIndexGiven;
    /// Первый индекс.
    int FirstIndex;

    /// Дан ли второй индекс.
    bool IsSecondIndexGiven;
    /// Второй индекс.
    int SecondIndex;

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

int InputAllOption(Args* pArgs);

int InputOrFillMatrix(Args* pArgs, Matrix* pMatrix);

#endif //ARGS_H
