#ifndef EATPHILOSOPHEROPTIONS_H
#define EATPHILOSOPHEROPTIONS_H

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
} EatPhilosopherOptions;

void* DoEatPhilosopherThread(void* pEatThreadOptions);

void* DoEatPhilosopherThread1(void* pEatThreadOptions);

EatPhilosopherOptions*
CreateEatPhilosopherOptions(Table* pTable, Philosopher* pPhilosopher,
                            pthread_mutex_t* mutex,
                            int minDurationEat,
                            int maxDurationEat,
                            sem_t* pArbitrator, bool isInfinityDuration);

void DestroyEatPhilosopherOptions(EatPhilosopherOptions* pOptions);

#include "Philosopher.h"

#endif //EATPHILOSOPHEROPTIONS_H
