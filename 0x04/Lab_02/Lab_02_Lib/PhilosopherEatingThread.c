/// \file
/// \brief Реализация функций из PhilosopherEatingThread.h
/// \details Реализация функций из PhilosopherEatingThread.h.

#include <malloc.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <limits.h>

#include "Utils.h"
#include "PhilosopherEatingThread.h"
#include "Logger.h"
#include "Macro.h"
#include "Philosopher.h"

PhilosopherEatingThreadOptions* CreatePhilosopherEatingThreadOptions(
        Table* pTable, Philosopher* pPhilosopher, pthread_mutex_t* pMutex)
{
    PhilosopherEatingThreadOptions* pOptions =
            (PhilosopherEatingThreadOptions*) malloc(
                    sizeof(PhilosopherEatingThreadOptions));
    FAILURE_IF_NULLPTR(pOptions);

    pOptions->pTable = pTable;
    pOptions->pPhilosopher = pPhilosopher;
    pOptions->pMutex = pMutex;

    return pOptions;
}

void DestroyPhilosopherEatingThreadOptions(
        PhilosopherEatingThreadOptions* pOptions)
{
    free(pOptions);
}

void* PhilosopherEatingThread(void* pEatThreadOptions)
{
    LOG("Запуск потока");

    srand(time(NULL));

    PhilosopherEatingThreadOptions* pOptions =
            (PhilosopherEatingThreadOptions*) pEatThreadOptions;

    Philosopher* pPhilosopher = pOptions->pPhilosopher;

    pthread_mutex_t* pMutex = pOptions->pMutex;

    pthread_mutex_lock(pMutex);
    pPhilosopher->IsThreadRunning = true;
    pthread_mutex_unlock(pMutex);

    while (!pOptions->pTable->IsEatingMustEnd)
    {
        sem_wait(pPhilosopher->pSemOnGoingToEat);

        pthread_mutex_lock(pMutex);

        if (pOptions->pTable->IsEatingMustEnd)
        {
            LOG("Поток для философа %d завершается",
                pPhilosopher->PhilosopherId);
            break;
        }

        struct timespec pDurationEat = RandomTimeMs(
                pPhilosopher->MinDurationEatMs,
                pPhilosopher->MaxDurationEatMs);


        LOG("Философ с номером %d начинает есть, смотрит на вилки",
            pPhilosopher->PhilosopherId);

        if (pPhilosopher->pLeftFork->IsInUse == false &&
            pPhilosopher->pRightFork->IsInUse == false)
        {
            LOG("Вилки свободны для философа с номером %d, начинает есть",
                pPhilosopher->PhilosopherId);

            pPhilosopher->IsEating = true;

            TakeOnFork(pPhilosopher->pLeftFork);

            TakeOnFork(pPhilosopher->pRightFork);

            LOG("Философ с номером %d начал есть %lf секунд",
                pPhilosopher->PhilosopherId,
                TimespecToDouble(pDurationEat,
                                 pOptions->pPhilosopher->IsInfinityDuration));

            pthread_mutex_unlock(pMutex);

            if (SleepOrWaitSem(pOptions->pPhilosopher->pSemOnWaitingEnding,
                               pDurationEat,
                               pOptions->pPhilosopher->IsInfinityDuration))
            {
                LOG("Приём пищи принудительно завершён заранее");
            }

            pthread_mutex_lock(pMutex);

            LOG("Закончил есть философ с номером %d",
                pPhilosopher->PhilosopherId);

            TakeOffFork(pPhilosopher->pLeftFork);

            TakeOffFork(pPhilosopher->pRightFork);

            pPhilosopher->IsEating = false;

            LOG("Поел, уходит философ с номером %d",
                pPhilosopher->PhilosopherId);

            pthread_mutex_unlock(pMutex);
        }
        else
        {
            pPhilosopher->IsWaiting = true;

            if (pPhilosopher->pLeftFork->IsInUse)
            {
                pPhilosopher->IsWaitingLeftFork = true;

                LOG("Левая вилка для философа с номером %d несвободна, "
                    "ожидание",
                    pPhilosopher->PhilosopherId);

                pthread_cond_wait(
                        pPhilosopher->pLeftFork->CondSignalOnRelease, pMutex);

                if (pPhilosopher->pLeftFork->IsInUse)
                {
                    LOG("Ожидание левой вилки для философа с номером %d "
                        "принудительно прервано",
                        pPhilosopher->PhilosopherId);

                    pPhilosopher->IsEating = false;
                    pPhilosopher->IsWaiting = false;
                    pPhilosopher->IsWaitingLeftFork = false;
                    pPhilosopher->IsWaitingRightFork = false;

                    LOG("Философ с номером %d принудительно уходит после "
                        "ожидания левой вилки",
                        pPhilosopher->PhilosopherId);
                    pthread_mutex_unlock(pMutex);
                    continue;
                }

                LOG("Освободилась левая вилка для философа с номером %d",
                    pPhilosopher->PhilosopherId);

                pPhilosopher->IsWaitingLeftFork = false;
            }

            LOG("Занятие левой вилки для философа с номером %d",
                pPhilosopher->PhilosopherId);

            TakeOnFork(pPhilosopher->pLeftFork);

            if (pPhilosopher->pRightFork->IsInUse)
            {
                pPhilosopher->IsWaitingRightFork = true;

                LOG("Правая вилка для философа с номером %d несвободна, "
                    "ожидание",
                    pPhilosopher->PhilosopherId);

                pthread_cond_wait(
                        pPhilosopher->pRightFork->CondSignalOnRelease,
                        pMutex);

                if (pPhilosopher->pRightFork->IsInUse)
                {
                    LOG("Ожидание правой вилки для философа с номером %d "
                        "принудительно прервано",
                        pPhilosopher->PhilosopherId);

                    TakeOffFork(pPhilosopher->pLeftFork);

                    pPhilosopher->IsEating = false;
                    pPhilosopher->IsWaiting = false;
                    pPhilosopher->IsWaitingLeftFork = false;
                    pPhilosopher->IsWaitingRightFork = false;

                    LOG("Философ с номером %d принудительно уходит после "
                        "ожидания левой вилки",
                        pPhilosopher->PhilosopherId);
                    pthread_mutex_unlock(pMutex);
                    continue;
                }

                LOG("Освободилась правая вилка для философа с номером %d",
                    pPhilosopher->PhilosopherId);

                pPhilosopher->IsWaitingRightFork = false;
            }
            LOG("Занятие правой вилки для философа с номером %d",
                pPhilosopher->PhilosopherId);

            TakeOnFork(pPhilosopher->pRightFork);

            LOG("Философ с номером %d ест после ожидания %lf сек.",
                pPhilosopher->PhilosopherId,
                TimespecToDouble(pDurationEat,
                                 pOptions->pPhilosopher->IsInfinityDuration));

            pPhilosopher->IsWaiting = false;
            pPhilosopher->IsEating = true;

            pthread_mutex_unlock(pMutex);

            if (SleepOrWaitSem(pOptions->pPhilosopher->pSemOnWaitingEnding,
                               pDurationEat,
                               pOptions->pPhilosopher->IsInfinityDuration))
            {
                LOG("Приём пищи после ожидания для философа с номером %d "
                    "завершён заранее сигналом",
                    pPhilosopher->PhilosopherId);
            }

            pthread_mutex_lock(pMutex);

            LOG("Философ с номером %d закончил есть",
                pPhilosopher->PhilosopherId);

            TakeOffFork(pPhilosopher->pLeftFork);

            TakeOffFork(pPhilosopher->pRightFork);

            pPhilosopher->IsEating = false;

            LOG("Философ с номером %d поел после ожидания, уходит",
                pPhilosopher->PhilosopherId);

            pthread_mutex_unlock(pMutex);
        }
    }

    pPhilosopher->IsThreadRunning = false;
    pthread_mutex_unlock(pMutex);

    LOG("Завершение потока");

    return pOptions;
}
