#include <malloc.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <limits.h>

#include "RealTimeTableStateThread.h"
#include "Utils.h"
#include "PhilosopherEatingThread.h"
#include "Log.h"
#include "Macro.h"

#define FILE_NAME "PhilosopherEatingThread"

const int NANOSEC_IN_SEC = 1000000000;

int SleepOrWaitSignal(Philosopher* pPhilosopher, struct timespec duration,
                      bool isInfinityDuration, pthread_mutex_t* pMutex)
{
    //struct timespec rem = {0, 0};
    if (isInfinityDuration)
    {
        pthread_mutex_lock(pMutex);
        struct timespec infinityTime = {INT_MAX, NANOSEC_IN_SEC - 1};
        int timedwaitReturns = pthread_cond_timedwait(
                pPhilosopher->pCondOnWaitingEnding, pMutex,
                &infinityTime);
        //LogPrefix(FILE_NAME);
        //printf("pthread_cond_timedwait вернул %d\n", timedwaitReturns);
        pthread_mutex_unlock(pMutex);
        return 1;
    }
    else
    {
        pthread_mutex_lock(pMutex);

        struct timespec currentTime;
        clock_gettime(CLOCK_REALTIME, &currentTime);

        struct timespec endTime = {currentTime.tv_sec + duration.tv_sec, currentTime.tv_nsec + duration.tv_nsec};
        if (endTime.tv_nsec >= NANOSEC_IN_SEC)
        {
            endTime.tv_sec++;
            endTime.tv_nsec -= NANOSEC_IN_SEC;
        }

        int timedwaitReturns = pthread_cond_timedwait(
                pPhilosopher->pCondOnWaitingEnding, pMutex,
                &endTime);
        //LogPrefix(FILE_NAME);
        //printf("pthread_cond_timedwait вернул %d\n", timedwaitReturns);
        pthread_mutex_unlock(pMutex);
        return 0;
    }
    return 0;
}

void* PhilosopherEatingThread(void* pEatThreadOptions)
{
    Log(FILE_NAME, "Запуск потока");

    srand(time(NULL));

    PhilosopherEatingThreadOptions* pEatOptions = (PhilosopherEatingThreadOptions*) pEatThreadOptions;

    Philosopher* pPh = pEatOptions->pPhilosopher;
    struct timespec pDurationEat = RandomTime(10, 10);
    pthread_mutex_t* pMutex = pEatOptions->pMutex;
    sem_t* pArbitrator = pEatOptions->pArbitrator;

    //pthread_cond_wait(pPh->OnGoingToEat, pMutex);

    LogTableInfo(pEatOptions->pTable);
    printf("[pid: 0x%08lx, philosopherId: %d] Пришёл есть\n",
           pthread_self(), pPh->PhilosopherId);
    pthread_mutex_lock(pMutex);
    pPh->IsThreadRunning = true;
    if (pPh->pLeftFork->IsInUse == false &&
        pPh->pRightFork->IsInUse == false)
    {
        LogTableInfo(pEatOptions->pTable);
        printf("[pid: 0x%08lx, philosopherId: %d] Вилки свободны, "
               "начинает есть %lf сек.\n", pthread_self(), pPh->PhilosopherId,
               TimespecToDouble(pDurationEat,
                       pEatOptions->pPhilosopher->IsInfinityDuration));

        pPh->IsEating = true;

//        int semValue;
//        sem_getvalue(pArbitrator, &semValue);
//        if (semValue == 0)
//        {
//            printf("[pid: %lu, philosopherId: %d] ожидание1\n",
//                   pthread_self(), pPh->PhilosopherId);
//        }
//        pthread_mutex_unlock(pMutex);
//        sem_wait(pArbitrator);
//        pthread_mutex_lock(pMutex);
//        pPh->pLeftFork->IsInUse = true;

        LogTableInfo(pEatOptions->pTable);
        TakeOnFork(pPh->pLeftFork, pMutex, pArbitrator);


//        sem_getvalue(pArbitrator, &semValue);
//        if (semValue == 0)
//        {
//            printf("[pid: %lu, philosopherId: %d] ожидание2\n",
//                   pthread_self(), pPh->PhilosopherId);
//        }
//        pthread_mutex_unlock(pMutex);
//        sem_wait(pArbitrator);
//        pthread_mutex_lock(pMutex);
//        pPh->pRightFork->IsInUse = true;

        LogTableInfo(pEatOptions->pTable);
        TakeOnFork(pPh->pRightFork, pMutex, pArbitrator);

        LogTableInfo(pEatOptions->pTable);
        printf("[pid: 0x%08lx, philosopherId: %d] Начал есть\n",
               pthread_self(), pPh->PhilosopherId);
        pthread_mutex_unlock(pMutex);

        if (SleepOrWaitSignal(pEatOptions->pPhilosopher, pDurationEat,
                              pEatOptions->pPhilosopher->IsInfinityDuration,
                              pEatOptions->pMutex))
        {
            LogTableInfo(pEatOptions->pTable);
            printf("[pid: 0x%08lx, philosopherId: %d] Приём пищи завершён заранее сигналом\n",
                   pthread_self(), pPh->PhilosopherId);
        }

        //nanosleep(&pDurationEat, NULL);
        pthread_mutex_lock(pMutex);
        LogTableInfo(pEatOptions->pTable);
        printf("[pid: 0x%08lx, philosopherId: %d] Закончил есть\n",
               pthread_self(), pPh->PhilosopherId);

        //pPh->pLeftFork->IsInUse = false;
        //pthread_cond_signal(pPh->pLeftFork->CondSignalOnRelease);
        //sem_post(pArbitrator);
        LogTableInfo(pEatOptions->pTable);
        TakeOffFork(pPh->pLeftFork, pMutex, pArbitrator);

        //pPh->pRightFork->IsInUse = false;
        //pthread_cond_signal(pPh->pRightFork->CondSignalOnRelease);
        //sem_post(pArbitrator);
        LogTableInfo(pEatOptions->pTable);
        TakeOffFork(pPh->pRightFork, pMutex, pArbitrator);

        pPh->IsEating = false;

        LogTableInfo(pEatOptions->pTable);
        printf("[pid: 0x%08lx, philosopherId: %d] Поел, уходит\n",
               pthread_self(), pPh->PhilosopherId);
        pthread_mutex_unlock(pMutex);
    }
    else
    {
        pPh->IsWaiting = true;

        if (pPh->pLeftFork->IsInUse)
        {
//            int semValue;
//            sem_getvalue(pArbitrator, &semValue);
//            if (semValue == 0)
//            {
//                printf("[pid: %lu, philosopherId: %d] Четыре вилки занято, ожидание\n",
//                       pthread_self(), pPh->PhilosopherId);
//            }
//            pthread_mutex_unlock(pMutex);
//            sem_wait(pArbitrator);
//            pthread_mutex_lock(pMutex);

            pPh->IsWaitingLeftFork = true;

            LogTableInfo(pEatOptions->pTable);
            printf("[pid: 0x%08lx, philosopherId: %d] Левая вилка несвободна, ожидание\n",
                   pthread_self(), pPh->PhilosopherId);

            pthread_cond_wait(pPh->pLeftFork->CondSignalOnRelease, pMutex);

            if (pPh->pLeftFork->IsInUse)
            {
                LogTableInfo(pEatOptions->pTable);
                printf("[pid: 0x%08lx, philosopherId: %d] Ожидание принудительно прервано (левая)\n",
                       pthread_self(), pPh->PhilosopherId);
                pthread_cond_wait(pPh->pLeftFork->CondSignalOnRelease,
                                  pMutex);
                //pthread_mutex_unlock(pMutex);
            }

            LogTableInfo(pEatOptions->pTable);
            printf("[pid: 0x%08lx, philosopherId: %d] Левая вилка освободилась, занятие...\n",
                   pthread_self(), pPh->PhilosopherId);

            pPh->IsWaitingLeftFork = false;

            //pPh->pLeftFork->IsInUse = true;

        }
        LogTableInfo(pEatOptions->pTable);
        printf("[pid: 0x%08lx, philosopherId: %d] Занятие левой вилки\n",
               pthread_self(), pPh->PhilosopherId);
        LogTableInfo(pEatOptions->pTable);
        TakeOnFork(pPh->pLeftFork, pMutex, pArbitrator);

        if (pPh->pRightFork->IsInUse)
        {
//            int semValue;
//            sem_getvalue(pArbitrator, &semValue);
//            if (semValue == 0)
//            {
//                printf("[pid: %lu, philosopherId: %d] Четыре вилки занято, ожидание\n",
//                       pthread_self(), pPh->PhilosopherId);
//            }
//            pthread_mutex_unlock(pMutex);
//            sem_wait(pArbitrator);
//            pthread_mutex_lock(pMutex);

            pPh->IsWaitingRightFork = true;

            LogTableInfo(pEatOptions->pTable);
            printf("[pid: 0x%08lx, philosopherId: %d] Правая вилка несвободна, ожидание...\n",
                   pthread_self(), pPh->PhilosopherId);

            pthread_cond_wait(pPh->pRightFork->CondSignalOnRelease, pMutex);

            if (pPh->pRightFork->IsInUse)
            {
                LogTableInfo(pEatOptions->pTable);
                printf("[pid: 0x%08lx, philosopherId: %d] Ожидание принудительно прервано (правая)\n",
                       pthread_self(), pPh->PhilosopherId);
                pthread_cond_wait(pPh->pRightFork->CondSignalOnRelease,
                                  pMutex);
                //pthread_mutex_unlock(pMutex);
            }

            LogTableInfo(pEatOptions->pTable);
            printf("[pid: 0x%08lx, philosopherId: %d] Правая вилка освободилась, занятие...\n",
                   pthread_self(), pPh->PhilosopherId);
            //LogTableInfo(pEatOptions->pTable);
            //pPh->pRightFork->IsInUse = true;
            pPh->IsWaitingRightFork = false;
        }
        LogTableInfo(pEatOptions->pTable);
        printf("[pid: 0x%08lx, philosopherId: %d] Занятие правой вилки\n",
               pthread_self(), pPh->PhilosopherId);
        LogTableInfo(pEatOptions->pTable);
        TakeOnFork(pPh->pRightFork, pMutex, pArbitrator);

        LogTableInfo(pEatOptions->pTable);
        printf("[pid: 0x%08lx, philosopherId: %d] Начинает есть после ожидания\n",
               pthread_self(), pPh->PhilosopherId);
        pPh->IsWaiting = false;
        pPh->IsEating = true;

        LogTableInfo(pEatOptions->pTable);
        printf("[pid: 0x%08lx, philosopherId: %d] Начал есть\n",
               pthread_self(), pPh->PhilosopherId);
        pthread_mutex_unlock(pMutex);

        if (SleepOrWaitSignal(pEatOptions->pPhilosopher, pDurationEat,
                              pEatOptions->pPhilosopher->IsInfinityDuration,
                              pEatOptions->pMutex))
        {
            LogTableInfo(pEatOptions->pTable);
            printf("[pid: 0x%08lx, philosopherId: %d] Приём пищи после ожидания завершён заранее сигналом\n",
                   pthread_self(), pPh->PhilosopherId);
        }

        pthread_mutex_lock(pMutex);
        LogTableInfo(pEatOptions->pTable);
        printf("[pid: 0x%08lx, philosopherId: %d] Закончил есть\n",
               pthread_self(), pPh->PhilosopherId);

//        sem_post(pArbitrator);
//        pPh->pLeftFork->IsInUse = false;
//        pthread_cond_signal(pPh->pLeftFork->CondSignalOnRelease);
        LogTableInfo(pEatOptions->pTable);
        TakeOffFork(pPh->pLeftFork, pMutex, pArbitrator);

//        sem_post(pArbitrator);
//        pPh->pRightFork->IsInUse = false;
//        pthread_cond_signal(pPh->pRightFork->CondSignalOnRelease);
        LogTableInfo(pEatOptions->pTable);
        TakeOffFork(pPh->pRightFork, pMutex, pArbitrator);

        pPh->IsEating = false;

        LogTableInfo(pEatOptions->pTable);
        printf("[pid: 0x%08lx, philosopherId: %d] Поел после ожидания, уходит\n",
               pthread_self(), pPh->PhilosopherId);
        pthread_mutex_unlock(pMutex);
    }

    pthread_mutex_lock(pMutex);
    pPh->IsThreadRunning = false;
    pthread_mutex_unlock(pMutex);

    return NULL;
}

void* PhilosopherEatingThread1(void* pEatThreadOptions)
{
    Log(FILE_NAME, "Запуск потока");

    srand(time(NULL));

    PhilosopherEatingThreadOptions* pOptions = (PhilosopherEatingThreadOptions*) pEatThreadOptions;

    Philosopher* pPhilosopher = pOptions->pPhilosopher;
    //struct timespec pDurationEat = pOptions->pDurationEat;
    pthread_mutex_t* pMutex = pOptions->pMutex;
    sem_t* pArbitrator = pOptions->pArbitrator;

    pthread_mutex_lock(pMutex);
    pPhilosopher->IsThreadRunning = true;
    pthread_mutex_unlock(pMutex);

    while (!pOptions->pTable->IsEatingMustEnd)
    {
        sem_wait(pPhilosopher->pSemOnGoingToEat);
        if (pOptions->pTable->IsEatingMustEnd)
        {
            Log(FILE_NAME, "Поток для философа %d завершается",
                   pPhilosopher->PhilosopherId);
            break;
        }

        struct timespec pDurationEat = RandomTime(
                pPhilosopher->MinDurationEat,
                pPhilosopher->MaxDurationEat);


        Log(FILE_NAME, "Начинает есть");

        pthread_mutex_lock(pMutex);
        if (pPhilosopher->pLeftFork->IsInUse == false &&
            pPhilosopher->pRightFork->IsInUse == false)
        {
            Log(FILE_NAME, "Вилки свободны для философа с номером %d, начинает есть %lf сек.",
                   pPhilosopher->PhilosopherId,
                   TimespecToDouble(pDurationEat,
                           pOptions->pPhilosopher->IsInfinityDuration));

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
            TakeOnFork(pPhilosopher->pLeftFork, pMutex, pArbitrator);


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
            TakeOnFork(pPhilosopher->pRightFork, pMutex, pArbitrator);

            Log(FILE_NAME, "Философ с номером %d начал есть %lf секунд",
                   pPhilosopher->PhilosopherId,
                   TimespecToDouble(pDurationEat, pOptions->pPhilosopher->IsInfinityDuration));

            // LogTableInfo(pOptions->pTable);
            //printf("[pid: 0x%08lx, philosopherId: %d] Начал есть\n",
            //       pthread_self(), pPhilosopher->PhilosopherId);
            pthread_mutex_unlock(pMutex);

            if (SleepOrWaitSignal(pOptions->pPhilosopher, pDurationEat,
                                  pOptions->pPhilosopher->IsInfinityDuration,
                                  pOptions->pMutex))
            {

                Log(FILE_NAME, "Приём пищи завершён заранее сигналом");
                //LogTableInfo(pOptions->pTable);
                //printf("[pid: 0x%08lx, philosopherId: %d] Приём пищи завершён заранее сигналом\n",
                //       pthread_self(), pPhilosopher->PhilosopherId);
            }

            //nanosleep(&pDurationEat, NULL);
            pthread_mutex_lock(pMutex);
            Log(FILE_NAME, "Закончил есть философ с номером %d",
                   pPhilosopher->PhilosopherId);
            //LogTableInfo(pOptions->pTable);
            //printf("[pid: 0x%08lx, philosopherId: %d] Закончил есть\n",
            //       pthread_self(), pPhilosopher->PhilosopherId);

            //pPhilosopher->pLeftFork->IsInUse = false;
            //pthread_cond_signal(pPhilosopher->pLeftFork->CondSignalOnRelease);
            //sem_post(pArbitrator);
            //LogTableInfo(pOptions->pTable);
            TakeOffFork(pPhilosopher->pLeftFork, pMutex, pArbitrator);

            //pPhilosopher->pRightFork->IsInUse = false;
            //pthread_cond_signal(pPhilosopher->pRightFork->CondSignalOnRelease);
            //sem_post(pArbitrator);
            //LogTableInfo(pOptions->pTable);
            TakeOffFork(pPhilosopher->pRightFork, pMutex, pArbitrator);

            pPhilosopher->IsEating = false;


            Log(FILE_NAME, "Поел, уходит философ с номером %d",
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

                Log(FILE_NAME, "Левая вилка для философа с номером %d несвободна, ожидание",
                       pPhilosopher->PhilosopherId);

                //LogTableInfo(pOptions->pTable);
                //printf("[pid: 0x%08lx, philosopherId: %d] Левая вилка несвободна, ожидание\n",
                //       pthread_self(), pPhilosopher->PhilosopherId);

                pthread_cond_wait(
                        pPhilosopher->pLeftFork->CondSignalOnRelease, pMutex);

                if (pPhilosopher->pLeftFork->IsInUse)
                {
                    Log(FILE_NAME, "Ожидание левой вилки для философа с номером %d принудительно прервано",
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

                    Log(FILE_NAME, "Философ с номером %d принудительно уходит после ожидания левой вилки",
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

                Log(FILE_NAME, "Освободилась левая вилка для философа с номером %d",
                       pPhilosopher->PhilosopherId);


                //LogTableInfo(pOptions->pTable);
                //printf("[pid: 0x%08lx, philosopherId: %d] Левая вилка освободилась, занятие...\n",
                //       pthread_self(), pPhilosopher->PhilosopherId);

                pPhilosopher->IsWaitingLeftFork = false;

                //pPhilosopher->pLeftFork->IsInUse = true;

            }

            Log(FILE_NAME, "Занятие левой вилки для философа с номером %d",
                   pPhilosopher->PhilosopherId);



            //LogTableInfo(pOptions->pTable);
            //printf("[pid: 0x%08lx, philosopherId: %d] Занятие левой вилки\n",//pthread_self(), pPhilosopher->PhilosopherId);
            //LogTableInfo(pOptions->pTable);
            TakeOnFork(pPhilosopher->pLeftFork, pMutex, pArbitrator);

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

                Log(FILE_NAME, "Правая вилка для философа с номером %d несвободна, ожидание",
                       pPhilosopher->PhilosopherId);


                //LogTableInfo(pOptions->pTable);
                //printf("[pid: 0x%08lx, philosopherId: %d] Правая вилка несвободна, ожидание...\n",
                //       pthread_self(), pPhilosopher->PhilosopherId);

                pthread_cond_wait(
                        pPhilosopher->pRightFork->CondSignalOnRelease,
                        pMutex);

                if (pPhilosopher->pRightFork->IsInUse)
                {
                    Log(FILE_NAME, "Ожидание правой вилки для философа с номером %d принудительно прервано",
                           pPhilosopher->PhilosopherId);

                    //LogPrefix(FILE_NAME);
                    //printf("Философ с номером %d закончил есть\n",
                    //       pPhilosopher->PhilosopherId);

                    //TakeOffFork(pPhilosopher->pLeftFork, pMutex, pArbitrator);

                    //TakeOffFork(pPhilosopher->pRightFork, pMutex, pArbitrator);

                    TakeOffFork(pPhilosopher->pLeftFork, pMutex, NULL);

                    pPhilosopher->IsEating = false;
                    pPhilosopher->IsWaiting = false;
                    pPhilosopher->IsWaitingLeftFork = false;
                    pPhilosopher->IsWaitingRightFork = false;

                    Log(FILE_NAME, "Философ с номером %d принудительно уходит после ожидания левой вилки",
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


                Log(FILE_NAME, "Освободилась правая вилка для философа с номером %d",
                       pPhilosopher->PhilosopherId);

                //LogTableInfo(pOptions->pTable);
                //printf("[pid: 0x%08lx, philosopherId: %d] Правая вилка освободилась, занятие...\n",
                //       pthread_self(), pPhilosopher->PhilosopherId);
                //LogTableInfo(pOptions->pTable);
                //pPhilosopher->pRightFork->IsInUse = true;
                pPhilosopher->IsWaitingRightFork = false;
            }
            Log(FILE_NAME, "Занятие правой вилки для философа с номером %d",
                   pPhilosopher->PhilosopherId);
            //LogTableInfo(pOptions->pTable);
            //printf("[pid: 0x%08lx, philosopherId: %d] Занятие правой вилки\n",
            //       pthread_self(), pPhilosopher->PhilosopherId);
            //LogTableInfo(pOptions->pTable);
            TakeOnFork(pPhilosopher->pRightFork, pMutex, pArbitrator);

            Log(FILE_NAME, "Философ с номером %d начинает есть после ожидания %lf сек.",
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

            if (SleepOrWaitSignal(pOptions->pPhilosopher, pDurationEat,
                                  pOptions->pPhilosopher->IsInfinityDuration,
                                  pOptions->pMutex))
            {

                Log(FILE_NAME, "Приём пищи после ожидания для философа с номером %d завершён заранее сигналом",
                       pPhilosopher->PhilosopherId);

                //LogTableInfo(pOptions->pTable);
                //printf("[pid: 0x%08lx, philosopherId: %d] Приём пищи после ожидания завершён заранее сигналом\n",
                //       pthread_self(), pPhilosopher->PhilosopherId);
            }

            pthread_mutex_lock(pMutex);
            Log(FILE_NAME, "Философ с номером %d закончил есть",
                   pPhilosopher->PhilosopherId);
            //LogTableInfo(pOptions->pTable);
            //printf("[pid: 0x%08lx, philosopherId: %d] Закончил есть\n",
            //       pthread_self(), pPhilosopher->PhilosopherId);

//        sem_post(pArbitrator);
//        pPhilosopher->pLeftFork->IsInUse = false;
//        pthread_cond_signal(pPhilosopher->pLeftFork->CondSignalOnRelease);
            //LogTableInfo(pOptions->pTable);
            TakeOffFork(pPhilosopher->pLeftFork, pMutex, pArbitrator);

//        sem_post(pArbitrator);
//        pPhilosopher->pRightFork->IsInUse = false;
//        pthread_cond_signal(pPhilosopher->pRightFork->CondSignalOnRelease);
            //LogTableInfo(pOptions->pTable);
            TakeOffFork(pPhilosopher->pRightFork, pMutex, pArbitrator);

            pPhilosopher->IsEating = false;

            Log(FILE_NAME, "Философ с номером %d поел после ожидания, уходит",
                   pPhilosopher->PhilosopherId);
            //LogTableInfo(pOptions->pTable);
            //printf("[pid: 0x%08lx, philosopherId: %d] Поел после ожидания, уходит\n",
            //       pthread_self(), pPhilosopher->PhilosopherId);
            pthread_mutex_unlock(pMutex);
        }
    }

    pthread_mutex_lock(pMutex);
    pPhilosopher->IsThreadRunning = false;
    pthread_mutex_unlock(pMutex);

    Log(FILE_NAME, "Завершение потока");

    //LogTableInfo(pOptions->pTable);
    //printf("[pid: 0x%08lx][PhilosopherEatingThread1] Завершение потока\n", pthread_self());

    return pOptions;
}

PhilosopherEatingThreadOptions*
CreatePhilosopherEatingThreadOptions(Table* pTable, Philosopher* pPhilosopher,
                                     pthread_mutex_t* mutex,
                                     sem_t* pArbitrator)
{
    PhilosopherEatingThreadOptions* pOptions = (PhilosopherEatingThreadOptions*) malloc(
            sizeof(PhilosopherEatingThreadOptions));
    FAILURE_IF_NULLPTR(pOptions);
    pOptions->pTable = pTable;
    pOptions->pPhilosopher = pPhilosopher;
    pOptions->pMutex = mutex;
    pOptions->pArbitrator = pArbitrator;
    return pOptions;
}

void DestroyPhilosopherEatingThreadOptions(
        PhilosopherEatingThreadOptions* pOptions)
{
    free(pOptions);
}