#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "AutoEatThread.h"
#include "Utils.h"
#include "RealTimeTableStateThread.h"
#include "Log.h"

#define FILE_NAME "AutoEatThread"

AutoEatThreadOptions* CreateAutoEatThreadOptions(Table* pTable)
{
    AutoEatThreadOptions* pOptions = (AutoEatThreadOptions*) malloc(
            sizeof(AutoEatThreadOptions));
    pOptions->pTable = pTable;
    //pOptions->IsMustStop = false;
    return pOptions;
}

void DestroyAutoEatThreadOptions(AutoEatThreadOptions* pOptions)
{
    free(pOptions);
}


int Eat1(Table* pTable, Philosopher* pPhilosopher, struct timespec tw1, int i)
{
    pthread_mutex_lock(pTable->pMutex);
    if (pPhilosopher->IsEating == true)
    {
        LogPrefix(FILE_NAME);
        printf("Философ с номером %d уже ест\n", pPhilosopher->PhilosopherId);
        pthread_mutex_unlock(pTable->pMutex);
        return 1;
    }
    if (pPhilosopher->IsWaiting == true)
    {
        LogPrefix(FILE_NAME);
        printf("Философ с номером %d ещё ожидает\n", pPhilosopher->PhilosopherId);
        pthread_mutex_unlock(pTable->pMutex);
        return 1;
    }
    pthread_mutex_unlock(pTable->pMutex);


    sem_post(pPhilosopher->pSemOnGoingToEat);
    //pthread_cond_signal(pPhilosopher->OnGoingToEat);
    return 0;
}

void* AutoEatThread(void* pAutoEatThreadOptions)
{
    AutoEatThreadOptions* pOptions = (AutoEatThreadOptions*) pAutoEatThreadOptions;

    srand(time(NULL));
    pOptions->pTable->IsEatingStarted = true;

    int i = 0;
    while (!pOptions->pTable->IsEatingMustEnd)
    {
        struct timespec twb = RandomTime(
                pOptions->pTable->MinSendIntervalDuration,
                pOptions->pTable->MaxSendIntervalDuration);

        int c = RandomInterval(0, PHILOSOPHERS_COUNT);
        Philosopher* pPhilosopher = pOptions->pTable->ppPhilosophers[c];

        LogPrefix(FILE_NAME);
        printf("Философ с номером %d отправлен есть\n", pPhilosopher->PhilosopherId);

        if (Eat1(pOptions->pTable, pPhilosopher, twb, i) == 1)
        {
            //continue;
        }

        LogPrefix(FILE_NAME);
        printf("После отправки философа с номером %d задержка перед отправкой следующего %lf сек.\n", pPhilosopher->PhilosopherId, TimespecToDouble(&twb));

        //LogTableInfo(pOptions->pTable);
        //printf("[pid: 0x%08lx, philosopherId: %d, i: %d] Задержка перед отправкой следующего %lf сек.\n",
        //       pthread_self(), pPhilosopher->PhilosopherId, i++, TimespecToDouble(&twb));
        nanosleep(&twb, NULL);
    }

    //pOptions->pTable->IsEatingEnded = true;

    LogPrefix(FILE_NAME);
    printf("Завершение потока\n");


    //LogTableInfo(pOptions->pTable);
    //printf("[pid: 0x%08lx][AutoEatThread] Завершение потока\n", pthread_self());

    return NULL;
}