#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>

#define DEFAULT_FILENAME "1.bin";
#define DEFAULT_META_FORMAT "Версия: %d; Размер записи: %ld; Кол-во записей: %d";
#define DEFAULT_FORMAT "Архипелаг: %s; Кол-во островов: %d; Кол-во обитаемых островов: %d";
#define DEFAULT_COUNT_FORMAT "Выведено %d записей";

typedef struct
{
    bool IsFileNameGiven;
    char* FileName;

    bool IsIsForceCreateGiven;
    bool IsForceCreate;

    bool IsMetaFormatGiven;
    char* MetaFormat;

    bool IsFormatGiven;
    char* Format;

    bool IsCountFormatGiven;
    char* CountFormat;

    bool IsOldNameGiven;
    char* OldName;

    bool IsIndexGiven;
    int Index;

    bool IsNameGiven;
    char* Name;

    bool IsCountIslandsGiven;
    int CountIslands;

    bool IsCountInhabitedIslandsGiven;
    int CountInhabitedIslands;

    bool IsIsHexDumpRequiredGiven;
    bool IsHexDumpRequired;

    bool IsIsRemoveSwapWithLastGiven;
    bool IsRemoveSwapWithLast;

    bool IsIsAndGiven;
    bool IsAnd;

    char** pExtraArgs;
} Args;

Args* CreateArgs();

void DestroyArgs(Args* pArgs);

Args* ParseArgs(int argc, char** argv);

#endif //ARGS_H
