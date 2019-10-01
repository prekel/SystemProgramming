#ifndef AUTOEATTHREAD_H
#define AUTOEATTHREAD_H

#include <stdbool.h>

#include "Table.h"

typedef struct
{
    Table* pTable;
    int MinSendIntervalDuration;
    int MaxSendIntervalDuration;
} AutoEatThreadOptions;

AutoEatThreadOptions*
CreateAutoEatThreadOptions(Table* pTable, int minSendIntervalDuration, int maxSendIntervalDuration);

void DestroyAutoEatThreadOptions(AutoEatThreadOptions* pOptions);

int Eat1(Table* pTable, Philosopher* pPhilosopher, struct timespec tw1, int i);

void* AutoEatThread(void* pAutoEatThreadOptions);

#endif // AUTOEATTHREAD_H
