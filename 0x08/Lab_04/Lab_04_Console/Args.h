#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>

#define DEFAULT_FILENAME "1.bin";
#define DEFAULT_META_FORMAT "%d %ld %d";
#define DEFAULT_FORMAT "%s %d %d";

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

    char** pExtraArgs;
} Args;

Args* CreateArgs();

void DestroyArgs(Args* pArgs);

Args* ParseArgs(int argc, char** argv);

#endif //ARGS_H
