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

/// \struct Args
///
/// Аргументы коммандной строки.
typedef struct
{
    /// Дан ли путь до файла.
    bool IsFilePathGiven;
    /// Путь до файла. Если не дан, по умолчанию DEFAULT_FILENAME.
    char* FilePath;

    bool IsIsReCreateGiven;
    /// Требуется ли пересоздавание (очистка, если файл существует) файла.
    bool IsReCreate;

    bool IsIsOpenOrCreateGiven;
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

    bool IsIsHexDumpRequiredGiven;
    /// Требуется вывести шестнадцатиречный дамп файла.
    bool IsHexDumpRequired;

    bool IsIsRemoveSwapWithLastGiven;
    /// Требуется ли при удалении архипелага их файла записать последний
    /// архпелаг на место удаляемого.
    bool IsRemoveSwapWithLast;

    bool IsIsPrintRequiredGiven;
    /// Требуется ли вывод архипелагов.
    bool IsPrintRequired;

    bool IsIsOrGiven;
    /// Требуется ли при команде print учитывать условия ипользуя дизъюнкцию.
    bool IsOr;

    /// Требуется ли вывод справки.
    bool IsHelpGiven;

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
/// \param nargc Кол-во аргументов в массиве (без последнего NULL-элемента).
/// \param nargv Массив аргументов, начинающийся на название комманды и
/// заканчивающийся NULL-элементом
/// \return Указатель на аргументы коммандной строки. NULL в случае ошибки
/// аллокации.
Args* ParseArgs(int nargc, char** nargv);

#endif //ARGS_H
