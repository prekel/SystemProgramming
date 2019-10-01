#ifndef TABLE_H
#define TABLE_H

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#include "Philosopher.h"
#include "Fork.h"

typedef struct
{
    Philosopher** ppPhilosophers;
    Fork** ppForks;
    bool IsEatingStarted;
    bool IsEatingEnded;
    pthread_mutex_t* pMutex;
    sem_t* pArbitrator;
} Table;

Table* CreateTable();

int Eat(Table* pTable, Philosopher* pPhilosopher, struct timespec tw1, int i);



void DoEatAll1(Table* pTable);

void DestroyTable(Table* pTable);

#endif // TABLE_H
