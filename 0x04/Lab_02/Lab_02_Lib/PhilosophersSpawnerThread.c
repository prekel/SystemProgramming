/// \file
/// \brief Реализация функций из PhilosophersWaiterThread.h
/// \details Реализация функций из PhilosophersWaiterThread.h.

#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "PhilosophersSpawnerThread.h"
#include "Utils.h"
#include "Logger.h"

PhilosophersSpawnerThreadOptions* CreatePhilosophersSpawnerThreadOptions(
        Table* pTable,
        int minSendIntervalDuration,
        int maxSendIntervalDuration)
{
    PhilosophersSpawnerThreadOptions* pOptions =
            (PhilosophersSpawnerThreadOptions*)
                    malloc(sizeof(PhilosophersSpawnerThreadOptions));
    FAILURE_IF_NULLPTR(pOptions);

    pOptions->pTable = pTable;

    pOptions->MinSendIntervalDuration = minSendIntervalDuration;
    pOptions->MaxSendIntervalDuration = maxSendIntervalDuration;

    pOptions->pMutex = pTable->pMutex;

    pOptions->OnSemQuit = (sem_t*) malloc(sizeof(sem_t));
    FAILURE_IF_NULLPTR(pOptions->OnSemQuit);
    sem_init(pOptions->OnSemQuit, 0, 0);

    return pOptions;
}

void DestroyPhilosophersSpawnerThreadOptions(
        PhilosophersSpawnerThreadOptions* pOptions)
{
    sem_destroy(pOptions->OnSemQuit);
    free(pOptions->OnSemQuit);
    free(pOptions);
}

int SpawnPhilosopher(Table* pTable, Philosopher* pPhilosopher)
{
    pthread_mutex_lock(pTable->pMutex);
    if (pPhilosopher->IsEating == true)
    {
        LOG("Философ с номером %d уже ест", pPhilosopher->PhilosopherId);
        pthread_mutex_unlock(pTable->pMutex);
        return 1;
    }
    if (pPhilosopher->IsWaiting == true)
    {
        LOG("Философ с номером %d ещё ожидает", pPhilosopher->PhilosopherId);
        pthread_mutex_unlock(pTable->pMutex);
        return 1;
    }

    pthread_mutex_unlock(pTable->pMutex);

    sem_post(pPhilosopher->pSemOnGoingToEat);

    return 0;
}

void* PhilosophersSpawnerThread(void* pAutoEatThreadOptions)
{
    LOG("Запуск потока");
    srand(time(NULL));

    PhilosophersSpawnerThreadOptions* pOptions =
            (PhilosophersSpawnerThreadOptions*) pAutoEatThreadOptions;

    pOptions->pTable->IsEatingStarted = true;

    while (!pOptions->pTable->IsEatingMustEnd)
    {
        struct timespec randomWaitTime = RandomTimeMs(
                pOptions->MinSendIntervalDuration,
                pOptions->MaxSendIntervalDuration);

        int c = RandomInterval(0, pOptions->pTable->PhilosophersCount);
        Philosopher* pPhilosopher = pOptions->pTable->ppPhilosophers[c];

        LOG("Философ с номером %d отправлен есть",
            pPhilosopher->PhilosopherId);

        if (SpawnPhilosopher(pOptions->pTable, pPhilosopher) == 1)
        {
            //LOG("Не удалось отправить есть философа с номером %d",
            //    pPhilosopher->PhilosopherId);
        }

        LOG("После отправки философа с номером %d задержка перед отправкой "
            "следующего %lf сек.",
            pPhilosopher->PhilosopherId,
            TimespecToDouble(randomWaitTime, false));

        if (SleepOrWaitSem(pOptions->OnSemQuit, randomWaitTime, false))
        {
            LOG("Принудительная остановка потока-спавнера");
            break;
        }
    }

    LOG("Завершение потока");

    return pOptions;
}
