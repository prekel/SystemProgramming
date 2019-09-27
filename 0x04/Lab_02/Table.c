#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Table.h"

#define PHILOSOPHERS_COUNT 5

Table* CreateTable()
{
    Table* pTable = (Table*) malloc(sizeof(Table));
    pTable->Forks = (Fork**) malloc(PHILOSOPHERS_COUNT * sizeof(Fork*));
    for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    {
        pTable->Forks[i] = CreateFork(i + 1);
    }

    pTable->Philosophers = (Philosopher**) malloc(
            PHILOSOPHERS_COUNT * sizeof(Philosopher*));

    for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    {
        Fork* lFork = pTable->Forks[i == 0 ? PHILOSOPHERS_COUNT - 1 : i - 1];
        pTable->Philosophers[i] =
                CreatePhilosopher(i + 1, lFork, pTable->Forks[i]);
    }

    return pTable;
}

void DoEatAll1()
{
    srand (time(NULL));


    for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    {
        int a = rand() % 10;
        struct timespec tw = {a, 0};

    }
}

void DestroyTable(Table* pTable)
{
    for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    {
        DestroyFork(pTable->Forks[i]);
        DestroyPhilosopher(pTable->Philosophers[i]);
    }
    free(pTable->Forks);
    free(pTable->Philosophers);
    free(pTable);
}