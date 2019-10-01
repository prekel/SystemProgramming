#include <malloc.h>
#include <stdio.h>

#include "Log.h"

char ForkToChar(Fork* fork)
{
    if (fork->IsInUse)
        return ',';
    else
        return '.';
}
char PhToChar(Philosopher* fork)
{
    if (fork->IsEating)
        return '=';
    if (fork->IsWaiting)
        return '?';
    else
        return '_';
}

char* TableInfo(Table* pTable)
{
    char* result = (char*)malloc((PHILOSOPHERS_COUNT * 2 + 1) * sizeof(char));
    for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    {
        result[i * 2] = PhToChar(pTable->ppPhilosophers[i]);
        result[i * 2 + 1] = ForkToChar(pTable->ppForks[i]);
    }
    result[PHILOSOPHERS_COUNT * 2] = '\0';
    return result;
}

void LogTableInfo(Table* pTable)
{
    char* tableInfo = TableInfo(pTable);
    fprintf(stdout, "[%s]", tableInfo);
    free(tableInfo);
}

void LogPrefix(char* fileName)
{
    char* info = TableInfo(g_pLoggingTable);
    printf("[%s][pid: 0x%08lx][%24s] ", info, pthread_self(), fileName);
    free(info);
}
