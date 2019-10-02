#ifndef PHILOSOPHERSWAITERTHREAD_H
#define PHILOSOPHERSWAITERTHREAD_H

#include "Table.h"

typedef struct {
    Table* pTable;
} PhilosophersWaiterThreadOptions;

PhilosophersWaiterThreadOptions* CreatePhilosophersWaiterThreadOptions
(Table* pTable);

void DestroyPhilosophersWaiterThreadOptions
        (PhilosophersWaiterThreadOptions* pOptions);

void* PhilosophersWaiterThread(void* pPhilosophersWaiterThreadOptions);

#endif //PHILOSOPHERSWAITERTHREAD_H
