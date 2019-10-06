#ifndef REALTIMETABLESTATETHREAD_H
#define REALTIMETABLESTATETHREAD_H

#include <time.h>

#include "Fork.h"
#include "Table.h"
#include "Philosopher.h"

typedef struct {
    struct timespec pWaitTime;
    Table* pTable;
    pthread_mutex_t* pMutex;
} RealTimeTableStateThreadOptions;

RealTimeTableStateThreadOptions* CreateRealTimeTableStateThreadOptions(Table* pTable, struct timespec pWaitTime);

void DestroyRealTimeTableStateThreadOptions(RealTimeTableStateThreadOptions* pOptions);

void* RealTimeTableStateThread(void* pThreadOptions);

#endif //REALTIMETABLESTATETHREAD_H
