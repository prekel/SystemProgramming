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
} PhilosopherEatingThreadOptions;

void* PhilosopherEatingThread(void* pEatThreadOptions);

void* PhilosopherEatingThread1(void* pEatThreadOptions);

PhilosopherEatingThreadOptions*
CreatePhilosopherEatingThreadOptions(Table* pTable, Philosopher* pPhilosopher,
                                     pthread_mutex_t* mutex,
                                     sem_t* pArbitrator);

void DestroyPhilosopherEatingThreadOptions(PhilosopherEatingThreadOptions* pOptions);

#endif //PHILOSOPHEREATINGTHREAD_H
