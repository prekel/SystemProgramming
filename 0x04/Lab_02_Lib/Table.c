#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Table.h"
#include "Input.h"
#include "Utils.h"
#include "EatPhilosopherOptions.h"
#include "RealTimeTableState.h"

Table* CreateTable()
{
    Table* pTable = (Table*) malloc(sizeof(Table));
    pTable->ppForks = (Fork**) malloc(PHILOSOPHERS_COUNT * sizeof(Fork*));
    for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    {
        pTable->ppForks[i] = CreateFork(i + 1);
    }

    pTable->ppPhilosophers = (Philosopher**) malloc(
            PHILOSOPHERS_COUNT * sizeof(Philosopher*));

    for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    {
        Fork* lFork = pTable->ppForks[i == 0 ? PHILOSOPHERS_COUNT - 1 : i - 1];
        pTable->ppPhilosophers[i] =
                CreatePhilosopher(i + 1, lFork, pTable->ppForks[i]);
    }

    pTable->IsEatingStarted = false;
    pTable->IsEatingEnded = false;


    pTable->pMutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(pTable->pMutex, NULL);

    pTable->pArbitrator = (sem_t*) malloc(sizeof(sem_t));
    sem_init(pTable->pArbitrator, 0, PHILOSOPHERS_COUNT);

    pTable->MinDurationEat = 3;
    pTable->MaxDurationEat = 10;

    pTable->MinSendIntervalDuration = 1;
    pTable->MaxSendIntervalDuration = 2;

    return pTable;
}


int Eat(Table* pTable, Philosopher* pPhilosopher, struct timespec tw, int i)
{
    pthread_mutex_lock(pTable->pMutex);
    if (pPhilosopher->IsEating == true)
    {
        LogTableInfo(pTable);
        printf("[pid: 0x%08lx, philosopherId: %d, i: %d] Уже ест\n",
               pthread_self(), pPhilosopher->PhilosopherId, i);
        pthread_mutex_unlock(pTable->pMutex);
        //struct timespec tw1 = RandomTime(1, 2);
        //nanosleep(&tw1, NULL);
        return 1;
    }
    //pthread_mutex_unlock(pTable->pMutex);
    //pthread_mutex_lock(pTable->pMutex);
    if (pPhilosopher->IsWaiting == true)
    {
        LogTableInfo(pTable);
        printf("[pid: 0x%08lx, philosopherId: %d, i: %d] Уже ожидает\n",
               pthread_self(), pPhilosopher->PhilosopherId, i);
        pthread_mutex_unlock(pTable->pMutex);
        //struct timespec tw1 = RandomTime(1, 2);
        //nanosleep(&tw1, NULL);
        return 1;
    }
    pthread_mutex_unlock(pTable->pMutex);

    EatPhilosopherOptions* options
            = CreateEatPhilosopherOptions(pTable, pPhilosopher,
                                          pTable->pMutex,
                                          pTable->MinDurationEat,
                                          pTable->MaxDurationEat,
                                          pTable->pArbitrator, 0);

    pthread_t threadId;

    LogTableInfo(pTable);
    printf("[pid: 0x%08lx, philosopherId: %d, i: %d] Идёт есть\n",
           pthread_self(), pPhilosopher->PhilosopherId, i);
    pthread_create(&threadId, NULL, DoEatPhilosopherThread1, options);

    pPhilosopher->pThread = threadId;

    return 0;
}

int Eat1(Table* pTable, Philosopher* pPhilosopher, struct timespec tw1, int i)
{
    pthread_mutex_lock(pTable->pMutex);
    if (pPhilosopher->IsEating == true)
    {
        LogTableInfo(pTable);
        printf("[pid: 0x%08lx, philosopherId: %d, i: %d] Уже ест\n",
               pthread_self(), pPhilosopher->PhilosopherId, i);
        pthread_mutex_unlock(pTable->pMutex);
        return 1;
    }
    if (pPhilosopher->IsWaiting == true)
    {
        LogTableInfo(pTable);
        printf("[pid: 0x%08lx, philosopherId: %d, i: %d] Уже ожидает\n",
               pthread_self(), pPhilosopher->PhilosopherId, i);
        pthread_mutex_unlock(pTable->pMutex);
        return 1;
    }
    pthread_mutex_unlock(pTable->pMutex);


    sem_post(pPhilosopher->pSemOnGoingToEat);
    //pthread_cond_signal(pPhilosopher->OnGoingToEat);
    return 0;
}

void StartAllThreads(Table* pTable)
{
    for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    {
        EatPhilosopherOptions* options
                = CreateEatPhilosopherOptions(
                        pTable,
                        pTable->ppPhilosophers[i],
                        pTable->pMutex,
                        pTable->MinDurationEat,
                        pTable->MaxDurationEat,
                        pTable->pArbitrator,
                        false);

        LogTableInfo(pTable);
        printf("[pid: 0x%08lx] Создан поток для философа %d\n",
               pthread_self(), pTable->ppPhilosophers[i]->PhilosopherId);
        pthread_create(&pTable->ppPhilosophers[i]->pThread, NULL, DoEatPhilosopherThread1, options);
    }
}

void DoEatAll(Table* pTable)
{
    srand(time(NULL));
    pTable->IsEatingStarted = true;

    //for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    for (int i = 0; i < 20000000; i++)
    {
        //int a = rand() % 10 + 1;
        //int a = ;
        //struct timespec tw = {a, 0};
        struct timespec tw = RandomTime(5, 15);

        int c = RandomInterval(0, PHILOSOPHERS_COUNT);
        Philosopher* ph = pTable->ppPhilosophers[c];

        //int c1 = CycleInputInt("!:", 5, NULL);
        //int c2 = getchar() - '0' - 1;
        //int c2 = getch() - '0' - 1;
        //printf("[%d]", c2);
        //if (!(0 <= c2 && c2 <= 4)) continue;
        //Philosopher* ph = pTable->ppPhilosophers[c2];

        if (Eat(pTable, ph, tw, i) == 1) continue;

        struct timespec twb = RandomTime(0, 2);
        LogTableInfo(pTable);
        printf("[pid: 0x%08lx, philosopherId: %d, i: %d] Задержка перед отправкой следующего %lf сек.\n",
               pthread_self(), ph->PhilosopherId, i, TimespecToDouble(&twb));
        nanosleep(&twb, NULL);
    }

    pTable->IsEatingEnded = true;
}

void DoEatAll1(Table* pTable)
{
    srand(time(NULL));
    pTable->IsEatingStarted = true;

    for (int i = 0; i < 20000000; i++)
    {
        struct timespec twb = RandomTime(pTable->MinSendIntervalDuration, pTable->MaxSendIntervalDuration);

        int c = RandomInterval(0, PHILOSOPHERS_COUNT);
        Philosopher* ph = pTable->ppPhilosophers[c];

        if (Eat1(pTable, ph, twb, i) == 1) continue;

        LogTableInfo(pTable);
        printf("[pid: 0x%08lx, philosopherId: %d, i: %d] Задержка перед отправкой следующего %lf сек.\n",
               pthread_self(), ph->PhilosopherId, i, TimespecToDouble(&twb));
        nanosleep(&twb, NULL);
    }

    pTable->IsEatingEnded = true;
}

void DestroyTable(Table* pTable)
{
    for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    {
        DestroyFork(pTable->ppForks[i]);
        DestroyPhilosopher(pTable->ppPhilosophers[i]);
    }
    pthread_mutex_destroy(pTable->pMutex);
    free(pTable->pMutex);
    sem_destroy(pTable->pArbitrator);
    free(pTable->pArbitrator);
    free(pTable->ppForks);
    free(pTable->ppPhilosophers);
    free(pTable);
}