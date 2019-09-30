#ifndef REALTIMETABLESTATE_H
#define REALTIMETABLESTATE_H

#include <time.h>

#include "Fork.h"
#include "Table.h"
#include "Philosopher.h"

typedef struct {
    struct timespec pWaitTime;
    Table* pTable;
} RealTimeTableStateOptions;

RealTimeTableStateOptions* CreateRealTimeTableStateOptions(Table* pTable, struct timespec pWaitTime);

void DestroyRealTimeTableStateOptions(RealTimeTableStateOptions* pOptions);

char ForkToChar(Fork* fork);

char PhToChar(Philosopher* fork);

char* TableInfo(Table* pTable);

void LogTableInfo(Table* pTable);

void* RealTimeTableStateThread(void* pThreadOptions);

#endif // REALTIMETABLESTATE_H
