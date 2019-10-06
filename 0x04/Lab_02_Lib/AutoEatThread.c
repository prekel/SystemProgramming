#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "AutoEatThread.h"
#include "Utils.h"
#include "Macro.h"
#include "Log.h"

#define FILE_NAME "AutoEatThread"

AutoEatThreadOptions*
CreateAutoEatThreadOptions(Table* pTable, int minSendIntervalDuration, int maxSendIntervalDuration)
{
    AutoEatThreadOptions* pOptions = (AutoEatThreadOptions*) malloc(
            sizeof(AutoEatThreadOptions));
    FAILURE_IF_NULLPTR(pOptions);

    pOptions->pTable = pTable;

    pOptions->MinSendIntervalDuration = minSendIntervalDuration;
    pOptions->MaxSendIntervalDuration = maxSendIntervalDuration;

    pOptions->pMutex = pTable->pMutex;

//    pOptions->OnCondQuit = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));
//    FAILURE_IF_NULLPTR(pOptions->OnCondQuit);
//    pthread_cond_init(pOptions->OnCondQuit, NULL);

    pOptions->OnSemQuit = (sem_t*) malloc(sizeof(sem_t));
    FAILURE_IF_NULLPTR(pOptions->OnSemQuit);
    sem_init(pOptions->OnSemQuit, 0, 0);

    return pOptions;
}

void DestroyAutoEatThreadOptions(AutoEatThreadOptions* pOptions)
{
    //pthread_cond_destroy(pOptions->OnCondQuit);
    //free(pOptions->OnCondQuit);
    sem_destroy(pOptions->OnSemQuit);
    free(pOptions->OnSemQuit);
    free(pOptions);
}

int Eat1(Table* pTable, Philosopher* pPhilosopher)
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
    //pthread_cond_signal(pPhilosopher->pCondOnGoingToEat);


    //sem_post(pPhilosopher->pSemOnGoingToEat);
    //pthread_cond_signal(pPhilosopher->OnGoingToEat);
    return 0;
}

void* AutoEatThread(void* pAutoEatThreadOptions)
{
    LOG("Запуск потока");
    srand(time(NULL));

    AutoEatThreadOptions* pOptions = (AutoEatThreadOptions*) pAutoEatThreadOptions;

    pOptions->pTable->IsEatingStarted = true;

    while (!pOptions->pTable->IsEatingMustEnd)
    {
        struct timespec twb = RandomTimeMs(
                pOptions->MinSendIntervalDuration,
                pOptions->MaxSendIntervalDuration);

        int c = RandomInterval(0, pOptions->pTable->PhilosophersCount);
        Philosopher* pPhilosopher = pOptions->pTable->ppPhilosophers[c];

        LOG("Философ с номером %d отправлен есть", pPhilosopher->PhilosopherId);

        if (Eat1(pOptions->pTable, pPhilosopher) == 1)
        {
            //continue;
        }

        LOG("После отправки философа с номером %d задержка перед отправкой следующего %lf сек.", pPhilosopher->PhilosopherId,
               TimespecToDouble(twb, false));

        //LogTableInfo(pOptions->pTable);
        //printf("[pid: 0x%08lx, philosopherId: %d, i: %d] Задержка перед отправкой следующего %lf сек.\n",
        //       pthread_self(), pPhilosopher->PhilosopherId, i++, TimespecToDouble(&twb));
        //pthread_mutex_lock(pOptions->pMutex);
        if (SleepOrWaitSem(pOptions->OnSemQuit, twb, false, pOptions->pMutex))
        {
            LOG("Принудительная остановка потока-спавнера");
            //pthread_mutex_unlock(pOptions->pMutex);
            break;
        }
        //pthread_mutex_unlock(pOptions->pMutex);
        //nanosleep(&twb, NULL);
    }

    //pOptions->pTable->IsEatingEnded = true;

    LOG("Завершение потока");


    //LogTableInfo(pOptions->pTable);
    //printf("[pid: 0x%08lx][AutoEatThread] Завершение потока\n", pthread_self());

    return NULL;
}