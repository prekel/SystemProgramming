#include <malloc.h>
#include <errno.h>

#include "RealTimeTableStateThread.h"
#include "Utils.h"
#include "PhilosopherEatingThread.h"

int SleepOrWaitSignal(struct timespec tw)
{
    struct timespec rem;
    nanosleep(&tw, &rem);
    if (errno == EINTR)
    {
        return 1;
    }
    return 0;
}

void* PhilosopherEatingThread(void* pEatThreadOptions)
{
    PhilosopherEatingThreadOptions* pEatOptions = (PhilosopherEatingThreadOptions*) pEatThreadOptions;

    Philosopher* pPh = pEatOptions->pPhilosopher;
    struct timespec pDurationEat = RandomTime(10,10);
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
               TimespecToDouble(&pDurationEat));

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

        if (SleepOrWaitSignal(pDurationEat))
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

        if (SleepOrWaitSignal(pDurationEat))
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
    PhilosopherEatingThreadOptions* pEatOptions = (PhilosopherEatingThreadOptions*) pEatThreadOptions;

    Philosopher* pPh = pEatOptions->pPhilosopher;
    //struct timespec pDurationEat = pEatOptions->pDurationEat;
    pthread_mutex_t* pMutex = pEatOptions->pMutex;
    sem_t* pArbitrator = pEatOptions->pArbitrator;

    while (true)
    {
        sem_wait(pPh->pSemOnGoingToEat);

        struct timespec pDurationEat = RandomTime(pEatOptions->MinDurationEat,
                                                  pEatOptions->MaxDurationEat);

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
                   "начинает есть %lf сек.\n", pthread_self(),
                   pPh->PhilosopherId,
                   TimespecToDouble(&pDurationEat));

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

            if (SleepOrWaitSignal(pDurationEat))
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

                pthread_cond_wait(pPh->pLeftFork->CondSignalOnRelease,
                                  pMutex);

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

                pthread_cond_wait(pPh->pRightFork->CondSignalOnRelease,
                                  pMutex);

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

            if (SleepOrWaitSignal(pDurationEat))
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
    }

    pthread_mutex_lock(pMutex);
    pPh->IsThreadRunning = false;
    pthread_mutex_unlock(pMutex);

    return NULL;
}

PhilosopherEatingThreadOptions*
CreatePhilosopherEatingThreadOptions(Table* pTable, Philosopher* pPhilosopher,
                                     pthread_mutex_t* mutex,
                                     int minDurationEat,
                                     int maxDurationEat,
                                     sem_t* pArbitrator, bool isInfinityDuration)
{
    PhilosopherEatingThreadOptions* pOptions = (PhilosopherEatingThreadOptions*) malloc(
            sizeof(PhilosopherEatingThreadOptions));
    pOptions->pTable = pTable;
    pOptions->pPhilosopher = pPhilosopher;
    pOptions->MinDurationEat = minDurationEat;
    pOptions->MaxDurationEat = maxDurationEat;
    pOptions->pMutex = mutex;
    pOptions->pArbitrator = pArbitrator;
    pOptions->IsInfinityDuration = isInfinityDuration;
    return pOptions;
}

void DestroyPhilosopherEatingThreadOptions(PhilosopherEatingThreadOptions* pOptions)
{
    free(pOptions);
}
