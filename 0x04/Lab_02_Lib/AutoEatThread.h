#ifndef AUTOEATTHREAD_H
#define AUTOEATTHREAD_H

#include <stdbool.h>

#include "Table.h"

typedef struct
{
    Table* pTable;
    int MinSendIntervalDuration;
    int MaxSendIntervalDuration;
    pthread_mutex_t* pMutex;
} AutoEatThreadOptions;

AutoEatThreadOptions*
CreateAutoEatThreadOptions(Table* pTable, int minSendIntervalDuration, int maxSendIntervalDuration);

void DestroyAutoEatThreadOptions(AutoEatThreadOptions* pOptions);

int Eat1(Table* pTable, Philosopher* pPhilosopher);

void* AutoEatThread(void* pAutoEatThreadOptions);

#endif // AUTOEATTHREAD_H