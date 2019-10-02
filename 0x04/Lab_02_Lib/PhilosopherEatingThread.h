#ifndef PHILOSOPHEREATINGTHREAD_H
#define PHILOSOPHEREATINGTHREAD_H

#include <pthread.h>
#include <semaphore.h>

#include "Table.h"
#include "Philosopher.h"

typedef struct
{
    Table* pTable;
    Philosopher* pPhilosopher;
    pthread_mutex_t* pMutex;
    sem_t* pArbitrator;
} PhilosopherEatingThreadOptions;

PhilosopherEatingThreadOptions*
CreatePhilosopherEatingThreadOptions(Table* pTable, Philosopher* pPhilosopher,
                                     pthread_mutex_t* mutex,
                                     sem_t* pArbitrator);

void DestroyPhilosopherEatingThreadOptions(PhilosopherEatingThreadOptions* pOptions);

void* PhilosopherEatingThread(void* pEatThreadOptions);

int InterruptEating(Philosopher* pPhilosopher, pthread_mutex_t* pMutex);

void* PhilosopherEatingThread1(void* pEatThreadOptions);

#endif //PHILOSOPHEREATINGTHREAD_H
