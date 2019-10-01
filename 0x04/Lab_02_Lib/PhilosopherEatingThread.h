#ifndef PHILOSOPHEREATINGTHREAD_H
#define PHILOSOPHEREATINGTHREAD_H

#include "Table.h"
#include "Philosopher.h"

typedef struct
{
    Table* pTable;
    Philosopher* pPhilosopher;
    pthread_mutex_t* pMutex;
    sem_t* pArbitrator;
    int MinDurationEat;
    int MaxDurationEat;
    bool IsInfinityDuration;
} PhilosopherEatingThreadOptions;

void* PhilosopherEatingThread(void* pEatThreadOptions);

void* PhilosopherEatingThread1(void* pEatThreadOptions);

PhilosopherEatingThreadOptions*
CreatePhilosopherEatingThreadOptions(Table* pTable, Philosopher* pPhilosopher,
                                     pthread_mutex_t* mutex,
                                     int minDurationEat,
                                     int maxDurationEat,
                                     sem_t* pArbitrator, bool isInfinityDuration);

void DestroyPhilosopherEatingThreadOptions(PhilosopherEatingThreadOptions* pOptions);

#endif //PHILOSOPHEREATINGTHREAD_H
