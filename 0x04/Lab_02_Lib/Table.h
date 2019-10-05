#ifndef TABLE_H
#define TABLE_H

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#include "Philosopher.h"
#include "Fork.h"

typedef struct
{
    int PhilosophersCount;
    Philosopher** ppPhilosophers;
    Fork** ppForks;
    bool IsEatingStarted;
    bool IsEatingEnded;
    bool IsEatingMustEnd;
    pthread_mutex_t* pMutex;
    sem_t* pArbitrator;
} Table;

Table* CreateTable(int philosophersCount, int minDurationEatMs, int maxDurationEatMs,
            bool isInfinityDuration);

int Eat(Table* pTable, Philosopher* pPhilosopher, struct timespec tw1, int i);

//int Eat1(Table* pTable, Philosopher* pPhilosopher, struct timespec tw1, int i);

void StartAllThreads(Table* pTable);

void DoEatAll(Table* pTable);

void DoEatAll1(Table* pTable);

void DestroyTable(Table* pTable);

#endif // TABLE_H
