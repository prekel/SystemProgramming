#include <stdio.h>
#include <time.h>
#include <malloc.h>

#include "RealTimeTableState.h"

RealTimeTableStateOptions* CreateRealTimeTableStateOptions(Table* pTable, struct timespec pWaitTime)
{
    RealTimeTableStateOptions* pOptions = (RealTimeTableStateOptions*) malloc(
            sizeof(RealTimeTableStateOptions));

    pOptions->pTable = pTable;
    pOptions->pWaitTime = pWaitTime;

    return pOptions;
}

void DestroyRealTimeTableStateOptions(RealTimeTableStateOptions* pOptions)
{
    free(pOptions);
}

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

void* RealTimeTableStateThread(void* pThreadOptions)
{
#ifdef LOGLEVEL_REALTIMESTATE
    RealTimeTableStateOptions* pOptions = (RealTimeTableStateOptions*) pThreadOptions;

    int k = 0;
    while (k < 1)
    {
        if (pOptions->pTable->IsEatingEnded)
        {
            k++;
        }
        nanosleep(&pOptions->pWaitTime, NULL);
        char* tableInfo = TableInfo(pOptions->pTable);
        fprintf(stderr, "[%s]\n", tableInfo);
        free(tableInfo);
    }

#endif
    return NULL;
}