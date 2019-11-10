/// \file
/// \brief Аргументы коммандной строки
/// \details Аргументы коммандной строки и их парсинг.

#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>

#define DEFAULT_FILENAME "file.bin";
#define DEFAULT_META_FORMAT "Версия: %d; Кол-во записей: %d; Размер записи: %d; Размер метаинформации: %d";
#define DEFAULT_FORMAT "Архипелаг: %s; Кол-во островов: %d; Кол-во обитаемых островов: %d";
#define DEFAULT_COUNT_FORMAT "Выведено %d записей";

#define OPT_STRING ":f:rpM:F:C:N:I:n:c:i:DsoPh"

#define OPT_FILENAME 'f'
#define OPT_FILENAME_USAGE "-f строка"
#define OPT_FILENAME_DESCRIPTION "Путь до файла."
#define OPT_RECREATE 'r'
#define OPT_RECREATE_USAGE "-r"
#define OPT_RECREATE_DESCRIPTION "Требуется ли пересоздание файла."
#define OPT_OPEN_OR_CREATE 'p'
#define OPT_OPEN_OR_CREATE_USAGE "-p"
#define OPT_OPEN_OR_CREATE_DESCRIPTION "Требуется ли создание файла."
#define OPT_META_FORMAT 'M'
#define OPT_META_FORMAT_USAGE "-M строка"
#define OPT_META_FORMAT_DESCRIPTION "Форматирование метаинформации."
#define OPT_FORMAT 'F'
#define OPT_FORMAT_USAGE "-F строка"
#define OPT_FORMAT_DESCRIPTION "Форматирвание архипелага."
#define OPT_COUNT_FORMAT 'C'
#define OPT_COUNT_FORMAT_USAGE "-C строка"
#define OPT_COUNT_FORMAT_DESCRIPTION "Форматирование архипелага."
#define OPT_OLD_NAME 'N'
#define OPT_OLD_NAME_USAGE "-N строка"
#define OPT_OLD_NAME_DESCRIPTION "Старое название (для изменения)."
#define OPT_INDEX 'I'
#define OPT_INDEX_USAGE "-I целое"
#define OPT_INDEX_DESCRIPTION "Индекс."
#define OPT_HEXDUMP 'D'
#define OPT_HEXDUMP_USAGE "-D"
#define OPT_HEXDUMP_DESCRIPTION "Требуется ли вывод шестнадцатиричного дампа."
#define OPT_REMOVE_SWAP_WITH_LAST 's'
#define OPT_REMOVE_SWAP_WITH_LAST_USAGE "-s"
#define OPT_REMOVE_SWAP_WITH_LAST_DESCRIPTION "Требуется ли удалять архипелага заменой его на последний."
#define OPT_OR 'o'
#define OPT_OR_USAGE "-o"
#define OPT_OR_DESCRIPTION "Требуется ли при выводе учитывать условия используя дизъюнкцию."
#define OPT_PRINT 'P'
#define OPT_PRINT_USAGE "-P"
#define OPT_PRINT_DESCRIPTION "Требуется ли вывод."
#define OPT_HELP 'h'
#define OPT_HELP_USAGE "-h"
#define OPT_HELP_DESCRIPTION "Требуется ли вывод справки."
#define OPT_NAME 'n'
#define OPT_NAME_USAGE "-n строка"
#define OPT_NAME_DESCRIPTION "Название."
#define OPT_COUNT_ISLANDS 'c'
#define OPT_COUNT_ISLANDS_USAGE "-c целое"
#define OPT_COUNT_ISLANDS_DESCRIPTION "Кол-во островов."
#define OPT_COUNT_INHABITED_ISLANDS 'i'
#define OPT_COUNT_INHABITED_ISLANDS_USAGE "-i целое"
#define OPT_COUNT_INHABITED_ISLANDS_DESCRIPTION "Кол-во обитаемых островов."
#define OPT_UNKNOWN '?'

/// \struct Args
///
/// Аргументы коммандной строки.
typedef struct
{
    /// Дан ли путь до файла.
    bool IsFilePathGiven;
    /// Путь до файла. Если не дан, по умолчанию DEFAULT_FILENAME.
    char* FilePath;

    /// Требуется ли пересоздавание (очистка, если файл существует) файла.
    bool IsReCreate;

    /// Требуется ли создать файл если не существует или открыть если сущ.
    bool IsOpenOrCreate;

    /// Дана ли строка форматирования для вывода метаинформции.
    bool IsMetaFormatGiven;
    /// Строка форматирования для вывода метаинформции. Если не дана,
    /// по умолчанию DEFAULT_META_FORMAT.
    char* MetaFormat;

    /// Дана ли строка форматирования для записи (архипелага).
    bool IsFormatGiven;
    /// Строка форматирования для записи (архипелага). Если не дана,
    /// по умолчанию DEFAULT_FORMAT
    char* Format;

    /// Дана ли строка форматирования кол-ва выведенных записей.
    bool IsCountFormatGiven;
    /// Строка форматирования кол-ва выведенных записей. Если не дана,
    /// по умолчанию DEFAULT_COUNT_FORMAT
    char* CountFormat;

    /// Дано ли старое имя архипелага.
    bool IsOldNameGiven;
    /// Старое имя архипелага.
    char* OldName;

    /// Дан ли индекс архипелага в файле.
    bool IsIndexGiven;
    /// Индекс архипелага в файле.
    int Index;

    /// Требуется вывести шестнадцатиречный дамп файла.
    bool IsHexDumpRequired;

    /// Требуется ли при удалении архипелага их файла записать последний
    /// архпелаг на место удаляемого.
    bool IsRemoveSwapWithLast;

    /// Требуется ли вывод архипелагов.
    bool IsPrintRequired;

    /// Требуется ли при команде print учитывать условия ипользуя дизъюнкцию.
    bool IsOr;

    /// Требуется ли вывод справки.
    bool IsHelpGiven;

    /// Дано ли имя архипелага.
    bool IsNameGiven;
    /// Имя архипелага.
    char* Name;

    /// Дано ли кол-во островов архипелага.
    bool IsCountIslandsGiven;
    /// Кол-во островов архипелага.
    int CountIslands;

    /// Дано ли кол-во обитаемых островов архипелага.
    bool IsCountInhabitedIslandsGiven;
    /// Кол-во островов архипелага.
    int CountInhabitedIslands;

    /// Дан ли неизвестный параметр.
    bool IsUnknownOptionGiven;
    /// Символ неизвестного параметра.
    char UnknownOption;

    /// Кол-во ргументов
    int CountArgs;
    /// Кол-во првильных аргументов (когда в значении стребуется число и дано
    /// число итд.).
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

#endif //ARGS_H
