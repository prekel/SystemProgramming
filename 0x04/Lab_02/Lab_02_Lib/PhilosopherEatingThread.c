/// \file
/// \brief Реализация функций из PhilosopherEatingThread.h
/// \details Реализация функций из PhilosopherEatingThread.h.

#include <malloc.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <limits.h>

#include "RealTimeTableStateThread.h"
#include "Utils.h"
#include "PhilosopherEatingThread.h"
#include "Logger.h"
#include "Macro.h"
#include "Philosopher.h"

PhilosopherEatingThreadOptions* CreatePhilosopherEatingThreadOptions(Table* pTable, Philosopher* pPhilosopher, pthread_mutex_t* pMutex)
{
    PhilosopherEatingThreadOptions* pOptions = (PhilosopherEatingThreadOptions*) malloc(
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

    PhilosopherEatingThreadOptions* pOptions = (PhilosopherEatingThreadOptions*) pEatThreadOptions;

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


        LOG("Философ с номером %d начинает есть, смотрит на вилки", pPhilosopher->PhilosopherId);

        //pthread_mutex_lock(pMutex);
        if (pPhilosopher->pLeftFork->IsInUse == false &&
            pPhilosopher->pRightFork->IsInUse == false)
        {
            LOG("Вилки свободны для философа с номером %d, начинает есть",
                   pPhilosopher->PhilosopherId);

            pPhilosopher->IsEating = true;

//        int semValue;
//        sem_getvalue(pArbitrator, &semValue);
//        if (semValue == 0)
//        {
//            printf("[pid: %lu, philosopherId: %d] ожидание1\n",
//                   pthread_self(), pPhilosopher->PhilosopherId);
//        }
//        pthread_mutex_unlock(pMutex);
//        sem_wait(pArbitrator);
//        pthread_mutex_lock(pMutex);
//        pPhilosopher->pLeftFork->IsInUse = true;

            //LogTableInfo(pOptions->pTable);
            TakeOnFork(pPhilosopher->pLeftFork);


//        sem_getvalue(pArbitrator, &semValue);
//        if (semValue == 0)
//        {
//            printf("[pid: %lu, philosopherId: %d] ожидание2\n",
//                   pthread_self(), pPhilosopher->PhilosopherId);
//        }
//        pthread_mutex_unlock(pMutex);
//        sem_wait(pArbitrator);
//        pthread_mutex_lock(pMutex);
//        pPhilosopher->pRightFork->IsInUse = true;

            //LogTableInfo(pOptions->pTable);
            TakeOnFork(pPhilosopher->pRightFork);

            LOG("Философ с номером %d начал есть %lf секунд",
                   pPhilosopher->PhilosopherId,
                   TimespecToDouble(pDurationEat, pOptions->pPhilosopher->IsInfinityDuration));

            // LogTableInfo(pOptions->pTable);
            //printf("[pid: 0x%08lx, philosopherId: %d] Начал есть\n",
            //       pthread_self(), pPhilosopher->PhilosopherId);

            pthread_mutex_unlock(pMutex);

            if (SleepOrWaitSem(pOptions->pPhilosopher->pSemOnWaitingEnding,
                               pDurationEat,
                               pOptions->pPhilosopher->IsInfinityDuration))
            {

                LOG("Приём пищи принудительно завершён заранее");
                //LogTableInfo(pOptions->pTable);
                //printf("[pid: 0x%08lx, philosopherId: %d] Приём пищи завершён заранее сигналом\n",
                //       pthread_self(), pPhilosopher->PhilosopherId);
            }

            pthread_mutex_lock(pMutex);

            LOG("Закончил есть философ с номером %d",
                   pPhilosopher->PhilosopherId);
            //LogTableInfo(pOptions->pTable);
            //printf("[pid: 0x%08lx, philosopherId: %d] Закончил есть\n",
            //       pthread_self(), pPhilosopher->PhilosopherId);

            //pPhilosopher->pLeftFork->IsInUse = false;
            //pthread_cond_signal(pPhilosopher->pLeftFork->CondSignalOnRelease);
            //sem_post(pArbitrator);
            //LogTableInfo(pOptions->pTable);
            TakeOffFork(pPhilosopher->pLeftFork);

            //pPhilosopher->pRightFork->IsInUse = false;
            //pthread_cond_signal(pPhilosopher->pRightFork->CondSignalOnRelease);
            //sem_post(pArbitrator);
            //LogTableInfo(pOptions->pTable);
            TakeOffFork(pPhilosopher->pRightFork);

            pPhilosopher->IsEating = false;


            LOG("Поел, уходит философ с номером %d",
                   pPhilosopher->PhilosopherId);

            //LogTableInfo(pOptions->pTable);
            //printf("[pid: 0x%08lx, philosopherId: %d] Поел, уходит\n",
            //       pthread_self(), pPhilosopher->PhilosopherId);
            pthread_mutex_unlock(pMutex);
        }
        else
        {
            pPhilosopher->IsWaiting = true;

            if (pPhilosopher->pLeftFork->IsInUse)
            {
//            int semValue;
//            sem_getvalue(pArbitrator, &semValue);
//            if (semValue == 0)
//            {
//                printf("[pid: %lu, philosopherId: %d] Четыре вилки занято, ожидание\n",
//                       pthread_self(), pPhilosopher->PhilosopherId);
//            }
//            pthread_mutex_unlock(pMutex);
//            sem_wait(pArbitrator);
//            pthread_mutex_lock(pMutex);

                pPhilosopher->IsWaitingLeftFork = true;

                LOG("Левая вилка для философа с номером %d несвободна, ожидание",
                       pPhilosopher->PhilosopherId);

                //LogTableInfo(pOptions->pTable);
                //printf("[pid: 0x%08lx, philosopherId: %d] Левая вилка несвободна, ожидание\n",
                //       pthread_self(), pPhilosopher->PhilosopherId);

                pthread_cond_wait(
                        pPhilosopher->pLeftFork->CondSignalOnRelease, pMutex);

                if (pPhilosopher->pLeftFork->IsInUse)
                {
                    LOG("Ожидание левой вилки для философа с номером %d принудительно прервано",
                           pPhilosopher->PhilosopherId);

                    //LogPrefix(FILE_NAME);
                    //printf("Философ с номером %d закончил есть\n",
                    //       pPhilosopher->PhilosopherId);

                    //TakeOffFork(pPhilosopher->pLeftFork, pMutex, pArbitrator);

                    //TakeOffFork(pPhilosopher->pRightFork, pMutex, pArbitrator);

                    pPhilosopher->IsEating = false;
                    pPhilosopher->IsWaiting = false;
                    pPhilosopher->IsWaitingLeftFork = false;
                    pPhilosopher->IsWaitingRightFork = false;

                    LOG("Философ с номером %d принудительно уходит после ожидания левой вилки",
                           pPhilosopher->PhilosopherId);
                    pthread_mutex_unlock(pMutex);
                    continue;

                    //LogTableInfo(pOptions->pTable);
                    //printf("[pid: 0x%08lx, philosopherId: %d] Ожидание принудительно прервано (левая)\n",
                    //       pthread_self(), pPhilosopher->PhilosopherId);
                    pthread_cond_wait(
                            pPhilosopher->pLeftFork->CondSignalOnRelease,
                            pMutex);
                    //pthread_mutex_unlock(pMutex);
                }

                LOG("Освободилась левая вилка для философа с номером %d",
                       pPhilosopher->PhilosopherId);


                //LogTableInfo(pOptions->pTable);
                //printf("[pid: 0x%08lx, philosopherId: %d] Левая вилка освободилась, занятие...\n",
                //       pthread_self(), pPhilosopher->PhilosopherId);

                pPhilosopher->IsWaitingLeftFork = false;

                //pPhilosopher->pLeftFork->IsInUse = true;

            }

            LOG("Занятие левой вилки для философа с номером %d",
                   pPhilosopher->PhilosopherId);



            //LogTableInfo(pOptions->pTable);
            //printf("[pid: 0x%08lx, philosopherId: %d] Занятие левой вилки\n",//pthread_self(), pPhilosopher->PhilosopherId);
            //LogTableInfo(pOptions->pTable);
            TakeOnFork(pPhilosopher->pLeftFork);

            if (pPhilosopher->pRightFork->IsInUse)
            {
//            int semValue;
//            sem_getvalue(pArbitrator, &semValue);
//            if (semValue == 0)
//            {
//                printf("[pid: %lu, philosopherId: %d] Четыре вилки занято, ожидание\n",
//                       pthread_self(), pPhilosopher->PhilosopherId);
//            }
//            pthread_mutex_unlock(pMutex);
//            sem_wait(pArbitrator);
//            pthread_mutex_lock(pMutex);

                pPhilosopher->IsWaitingRightFork = true;

                LOG("Правая вилка для философа с номером %d несвободна, ожидание",
                       pPhilosopher->PhilosopherId);


                //LogTableInfo(pOptions->pTable);
                //printf("[pid: 0x%08lx, philosopherId: %d] Правая вилка несвободна, ожидание...\n",
                //       pthread_self(), pPhilosopher->PhilosopherId);

                pthread_cond_wait(
                        pPhilosopher->pRightFork->CondSignalOnRelease,
                        pMutex);

                if (pPhilosopher->pRightFork->IsInUse)
                {
                    LOG("Ожидание правой вилки для философа с номером %d принудительно прервано",
                           pPhilosopher->PhilosopherId);

                    //LogPrefix(FILE_NAME);
                    //printf("Философ с номером %d закончил есть\n",
                    //       pPhilosopher->PhilosopherId);

                    //TakeOffFork(pPhilosopher->pLeftFork, pMutex, pArbitrator);

                    //TakeOffFork(pPhilosopher->pRightFork, pMutex, pArbitrator);

                    TakeOffFork(pPhilosopher->pLeftFork);

                    pPhilosopher->IsEating = false;
                    pPhilosopher->IsWaiting = false;
                    pPhilosopher->IsWaitingLeftFork = false;
                    pPhilosopher->IsWaitingRightFork = false;

                    LOG("Философ с номером %d принудительно уходит после ожидания левой вилки",
                           pPhilosopher->PhilosopherId);
                    pthread_mutex_unlock(pMutex);
                    continue;

                    //LogTableInfo(pOptions->pTable);
                    //printf("[pid: 0x%08lx, philosopherId: %d] Ожидание принудительно прервано (правая)\n",
                    //       pthread_self(), pPhilosopher->PhilosopherId);
                    pthread_cond_wait(
                            pPhilosopher->pRightFork->CondSignalOnRelease,
                            pMutex);
                    //pthread_mutex_unlock(pMutex);
                }


                LOG("Освободилась правая вилка для философа с номером %d",
                       pPhilosopher->PhilosopherId);

                //LogTableInfo(pOptions->pTable);
                //printf("[pid: 0x%08lx, philosopherId: %d] Правая вилка освободилась, занятие...\n",
                //       pthread_self(), pPhilosopher->PhilosopherId);
                //LogTableInfo(pOptions->pTable);
                //pPhilosopher->pRightFork->IsInUse = true;
                pPhilosopher->IsWaitingRightFork = false;
            }
            LOG("Занятие правой вилки для философа с номером %d",
                   pPhilosopher->PhilosopherId);
            //LogTableInfo(pOptions->pTable);
            //printf("[pid: 0x%08lx, philosopherId: %d] Занятие правой вилки\n",
            //       pthread_self(), pPhilosopher->PhilosopherId);
            //LogTableInfo(pOptions->pTable);
            TakeOnFork(pPhilosopher->pRightFork);

            LOG("Философ с номером %d ест после ожидания %lf сек.",
                   pPhilosopher->PhilosopherId,
                   TimespecToDouble(pDurationEat, pOptions->pPhilosopher->IsInfinityDuration));
            //LogTableInfo(pOptions->pTable);
            //printf("[pid: 0x%08lx, philosopherId: %d] Начинает есть после ожидания\n",
            //       pthread_self(), pPhilosopher->PhilosopherId);
            pPhilosopher->IsWaiting = false;
            pPhilosopher->IsEating = true;

            //LogPrefix(FILE_NAME);
            //printf("Философ с номером %d начинает есть после ожидания\n", pPhilosopher->PhilosopherId);
            //LogTableInfo(pOptions->pTable);
            //printf("[pid: 0x%08lx, philosopherId: %d] Начал есть\n",
            //       pthread_self(), pPhilosopher->PhilosopherId);

            pthread_mutex_unlock(pMutex);

            if (SleepOrWaitSem(pOptions->pPhilosopher->pSemOnWaitingEnding,
                               pDurationEat,
                               pOptions->pPhilosopher->IsInfinityDuration))
            {

                LOG("Приём пищи после ожидания для философа с номером %d завершён заранее сигналом",
                       pPhilosopher->PhilosopherId);

                //LogTableInfo(pOptions->pTable);
                //printf("[pid: 0x%08lx, philosopherId: %d] Приём пищи после ожидания завершён заранее сигналом\n",
                //       pthread_self(), pPhilosopher->PhilosopherId);
            }

            pthread_mutex_lock(pMutex);

            LOG("Философ с номером %d закончил есть",
                   pPhilosopher->PhilosopherId);
            //LogTableInfo(pOptions->pTable);
            //printf("[pid: 0x%08lx, philosopherId: %d] Закончил есть\n",
            //       pthread_self(), pPhilosopher->PhilosopherId);

//        sem_post(pArbitrator);
//        pPhilosopher->pLeftFork->IsInUse = false;
//        pthread_cond_signal(pPhilosopher->pLeftFork->CondSignalOnRelease);
            //LogTableInfo(pOptions->pTable);
            TakeOffFork(pPhilosopher->pLeftFork);

//        sem_post(pArbitrator);
//        pPhilosopher->pRightFork->IsInUse = false;
//        pthread_cond_signal(pPhilosopher->pRightFork->CondSignalOnRelease);
            //LogTableInfo(pOptions->pTable);
            TakeOffFork(pPhilosopher->pRightFork);

            pPhilosopher->IsEating = false;

            LOG("Философ с номером %d поел после ожидания, уходит",
                   pPhilosopher->PhilosopherId);
            //LogTableInfo(pOptions->pTable);
            //printf("[pid: 0x%08lx, philosopherId: %d] Поел после ожидания, уходит\n",
            //       pthread_self(), pPhilosopher->PhilosopherId);
            pthread_mutex_unlock(pMutex);
        }
    }

    //pthread_mutex_lock(pMutex);
    pPhilosopher->IsThreadRunning = false;
    pthread_mutex_unlock(pMutex);

    LOG("Завершение потока");

    //LogTableInfo(pOptions->pTable);
    //printf("[pid: 0x%08lx][PhilosopherEatingThread1] Завершение потока\n", pthread_self());

    return pOptions;
}
