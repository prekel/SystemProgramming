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
    struct timespec pDurationEat;
} EatPhilosopherOptions;

void* DoEatPhilosopherThread(void* pEatThreadOptions);

EatPhilosopherOptions*
CreateEatPhilosopherOptions(Table* pTable, Philosopher* pPhilosopher,
                            pthread_mutex_t* mutex,
                            struct timespec durationEat, sem_t* pArbitrator);

void DestroyEatPhilosopherOptions(EatPhilosopherOptions* pOptions);

#include "Philosopher.h"

#endif //EATPHILOSOPHEROPTIONS_H
