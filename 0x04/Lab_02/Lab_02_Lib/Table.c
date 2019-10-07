/// \file
/// \brief Реализация функций из Table.h
/// \details Реализация функций из Table.h.

#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "Table.h"
#include "Input.h"
#include "PhilosopherEatingThread.h"
#include "Logger.h"
#include "Macro.h"

Table* CreateTable(int philosophersCount, int minDurationEatMs,
                   int maxDurationEatMs, bool isInfinityDuration)
{
    Table* pTable = (Table*) malloc(sizeof(Table));
    FAILURE_IF_NULLPTR(pTable);

    pTable->PhilosophersCount = philosophersCount;

    pTable->ppForks =
            (Fork**) malloc(pTable->PhilosophersCount * sizeof(Fork*));
    FAILURE_IF_NULLPTR(pTable->ppForks);
    for (int i = 0; i < pTable->PhilosophersCount; i++)
    {
        pTable->ppForks[i] = CreateFork(i + 1);
    }

    pTable->ppPhilosophers = (Philosopher**) malloc(
            pTable->PhilosophersCount * sizeof(Philosopher*));
    FAILURE_IF_NULLPTR(pTable->ppPhilosophers);

    for (int i = 0; i < pTable->PhilosophersCount; i++)
    {
        Fork* lFork = pTable->ppForks[i == 0 ?
                                      pTable->PhilosophersCount - 1 : i - 1];
        pTable->ppPhilosophers[i] =
                CreatePhilosopher(i + 1,
                                  lFork,
                                  pTable->ppForks[i],
                                  minDurationEatMs,
                                  maxDurationEatMs,
                                  isInfinityDuration);
    }

    pTable->IsEatingStarted = false;
    pTable->IsEatingEnded = false;
    pTable->IsEatingMustEnd = false;

    pTable->pMutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
    FAILURE_IF_NULLPTR(pTable->pMutex);
    pthread_mutex_init(pTable->pMutex, NULL);

    return pTable;
}

void StartAllThreads(Table* pTable)
{
    for (int i = 0; i < pTable->PhilosophersCount; i++)
    {
        PhilosopherEatingThreadOptions* options
                = CreatePhilosopherEatingThreadOptions(
                        pTable,
                        pTable->ppPhilosophers[i],
                        pTable->pMutex);

        LOG("Создан поток для философа %d",
            pTable->ppPhilosophers[i]->PhilosopherId);

        pthread_create(&pTable->ppPhilosophers[i]->pThread, NULL,
                       PhilosopherEatingThread, options);
    }
}

void DestroyTable(Table* pTable)
{
    for (int i = 0; i < pTable->PhilosophersCount; i++)
    {
        DestroyFork(pTable->ppForks[i]);
        DestroyPhilosopher(pTable->ppPhilosophers[i]);
    }
    pthread_mutex_destroy(pTable->pMutex);
    free(pTable->pMutex);
    free(pTable->ppForks);
    free(pTable->ppPhilosophers);
    free(pTable);
}
