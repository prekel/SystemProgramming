#include <stdio.h>
#include <time.h>
#include <malloc.h>

#include "RealTimeTableStateThread.h"

RealTimeTableStateThreadOptions* CreateRealTimeTableStateThreadOptions(Table* pTable, struct timespec pWaitTime)
{
    RealTimeTableStateThreadOptions* pOptions = (RealTimeTableStateThreadOptions*) malloc(
            sizeof(RealTimeTableStateThreadOptions));

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
#ifdef LOGLEVEL_REALTIMESTATE
    RealTimeTableStateThreadOptions* pOptions = (RealTimeTableStateThreadOptions*) pThreadOptions;

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