#include <stdio.h>
#include <time.h>
#include <malloc.h>

#include "RealTimeTableStateThread.h"
#include "Log.h"
#include "Macro.h"

#define FILE_NAME "RealTimeTableStateThread"

RealTimeTableStateThreadOptions* CreateRealTimeTableStateThreadOptions(Table* pTable, struct timespec pWaitTime)
{
    RealTimeTableStateThreadOptions* pOptions = (RealTimeTableStateThreadOptions*) malloc(
            sizeof(RealTimeTableStateThreadOptions));
    FAILURE_IF_NULLPTR(pOptions);

    pOptions->pTable = pTable;
    pOptions->pWaitTime = pWaitTime;

    return pOptions;
}

void DestroyRealTimeTableStateThreadOptions(RealTimeTableStateThreadOptions* pOptions)
{
    free(pOptions);
}

void* RealTimeTableStateThread(void* pThreadOptions)
{
    LogPrefix(FILE_NAME);
    printf("Запуск потока\n");

    RealTimeTableStateThreadOptions* pOptions = (RealTimeTableStateThreadOptions*) pThreadOptions;

#ifdef LOGLEVEL_REALTIMESTATE
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

    LogPrefix(FILE_NAME);
    printf("Завершение потока\n");

    //LogTableInfo(pOptions->pTable);
    //printf("[pid: 0x%08lx][RealTimeTableStateThread] Завершение потока\n", pthread_self());

    return NULL;
}