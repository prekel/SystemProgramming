#include <pthread.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "PhilosophersWaiterThread.h"
#include "Log.h"
#include "PhilosopherEatingThread.h"
#include "Macro.h"

#define FILE_NAME "PhilosophersWaiterThread"

PhilosophersWaiterThreadOptions* CreatePhilosophersWaiterThreadOptions
        (Table* pTable)
{
    PhilosophersWaiterThreadOptions* pOptions =
            (PhilosophersWaiterThreadOptions*)malloc(sizeof
            (PhilosophersWaiterThreadOptions));
    FAILURE_IF_NULLPTR(pOptions);

    pOptions->pTable = pTable;

    pOptions->pMutex = pTable->pMutex;

    return pOptions;
}

void DestroyPhilosophersWaiterThreadOptions
(PhilosophersWaiterThreadOptions* pOptions)
{
    free(pOptions);
}

void* PhilosophersWaiterThread(void* pPhilosophersWaiterThreadOptions)
{
    Log(FILE_NAME, "Запуск потока");

    PhilosophersWaiterThreadOptions* pOptions =
            (PhilosophersWaiterThreadOptions*)
            pPhilosophersWaiterThreadOptions;

    for (int i = 0; i < pOptions->pTable->PhilosophersCount; i++)
    {
        pthread_mutex_lock(pOptions->pTable->pMutex);
        if (pOptions->pTable->ppPhilosophers[i]->IsThreadRunning)
        {
            Log(FILE_NAME, "Ожидание завершения потока философа %d", pOptions->pTable->ppPhilosophers[i]->PhilosopherId);

            //LogTableInfo(pTable);
            //printf("[pid: 0x%08lx] Ожидание завершения потока философа %d\n",
            //       pthread_self(), pTable->ppPhilosophers[i]->PhilosopherId);
            sem_post(pOptions->pTable->ppPhilosophers[i]->pSemOnGoingToEat);
            pthread_mutex_unlock(pOptions->pTable->pMutex);
            void* pReturned;
            pthread_join(pOptions->pTable->ppPhilosophers[i]->pThread, &pReturned);
            PhilosopherEatingThreadOptions* pReturnedOptions =
                    (PhilosopherEatingThreadOptions*)pReturned;
            DestroyPhilosopherEatingThreadOptions(pReturnedOptions);
            continue;
        }
        pthread_mutex_unlock(pOptions->pTable->pMutex);
    }

    pthread_mutex_lock(pOptions->pTable->pMutex);
    pOptions->pTable->IsEatingEnded = true;
    pthread_mutex_unlock(pOptions->pTable->pMutex);

    Log(FILE_NAME, "Завершение потока");

    return NULL;
}