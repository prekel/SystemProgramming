#include <malloc.h>

#include "RealTimeTableState.h"
#include "Utils.h"
#include "EatPhilosopherOptions.h"

void* DoEatPhilosopherThread(void* pEatThreadOptions)
{
    EatPhilosopherOptions* pEatOptions = (EatPhilosopherOptions*) pEatThreadOptions;

    Philosopher* pPh = pEatOptions->pPhilosopher;
    struct timespec pDurationEat = pEatOptions->pDurationEat;
    pthread_mutex_t* pMutex = pEatOptions->pMutex;
    sem_t* pArbitrator = pEatOptions->pArbitrator;


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
        nanosleep(&pDurationEat, NULL);
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



            LogTableInfo(pEatOptions->pTable);
            printf("[pid: 0x%08lx, philosopherId: %d] Левая вилка несвободна, ожидание\n",
                   pthread_self(), pPh->PhilosopherId);

            pthread_cond_wait(pPh->pLeftFork->CondSignalOnRelease, pMutex);

            LogTableInfo(pEatOptions->pTable);
            printf("[pid: 0x%08lx, philosopherId: %d] Левая вилка освободилась, занятие...\n",
                   pthread_self(), pPh->PhilosopherId);

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

            LogTableInfo(pEatOptions->pTable);
            printf("[pid: 0x%08lx, philosopherId: %d] Правая вилка несвободна, ожидание...\n",
                   pthread_self(), pPh->PhilosopherId);

            pthread_cond_wait(pPh->pRightFork->CondSignalOnRelease, pMutex);

            LogTableInfo(pEatOptions->pTable);
            printf("[pid: 0x%08lx, philosopherId: %d] Правая вилка освободилась, занятие...\n",
                   pthread_self(), pPh->PhilosopherId);
            //LogTableInfo(pEatOptions->pTable);
            //pPh->pRightFork->IsInUse = true;
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
        nanosleep(&pDurationEat, NULL);
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

EatPhilosopherOptions* CreateEatPhilosopherOptions(Table* pTable, Philosopher* pPhilosopher,
                                                   pthread_mutex_t* mutex,
                                                   struct timespec durationEat, sem_t* pArbitrator)
{
    EatPhilosopherOptions* pOptions = (EatPhilosopherOptions*)malloc(
            sizeof(EatPhilosopherOptions));
    pOptions->pTable = pTable;
    pOptions->pPhilosopher = pPhilosopher;
    pOptions->pDurationEat = durationEat;
    pOptions->pMutex = mutex;
    pOptions->pArbitrator = pArbitrator;
    return pOptions;
}

void DestroyEatPhilosopherOptions(EatPhilosopherOptions* pOptions)
{
    free(pOptions);
}