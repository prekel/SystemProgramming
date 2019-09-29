#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Table.h"
#include "Utils.h"

#define PHILOSOPHERS_COUNT 5

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

    return pTable;
}

void DoEatAll1(Table* pTable)
{
    srand(time(NULL));
    pTable->IsEatingStarted = true;

    //for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    for (int i = 0; i < 20000000; i++)
    {
        //int a = rand() % 10 + 1;
        //int a = ;
        int c = RandomInterval(0, PHILOSOPHERS_COUNT);
        //struct timespec tw = {a, 0};
        struct timespec tw = RandomTime(10, 20);

        Philosopher* ph = pTable->ppPhilosophers[c];

        pthread_mutex_lock(pTable->pMutex);
        if (ph->IsEating == true)
        {
            printf("[pid: %lu, philosopherId: %d, i: %d] Уже ест\n",
                   pthread_self(), ph->PhilosopherId, i);
            pthread_mutex_unlock(pTable->pMutex);
            struct timespec tw1 = RandomTime(1, 2);
            nanosleep(&tw1, NULL);
            continue;
        }
        pthread_mutex_unlock(pTable->pMutex);
        pthread_mutex_lock(pTable->pMutex);
        if (ph->IsWaiting == true)
        {
            printf("[pid: %lu, philosopherId: %d, i: %d] Уже ожидает\n",
                   pthread_self(), ph->PhilosopherId, i);
            pthread_mutex_unlock(pTable->pMutex);
            struct timespec tw1 = RandomTime(1, 2);
            nanosleep(&tw1, NULL);
            continue;
        }
        pthread_mutex_unlock(pTable->pMutex);

        EatPhilosopherOptions* options
                = CreateEatPhilosopherOptions(ph, pTable->pMutex, &tw, pTable->pArbitrator);

        pthread_t threadId;

        printf("[pid: %lu, philosopherId: %d, i: %d] Идёт есть\n",
               pthread_self(), ph->PhilosopherId, i);
        pthread_create(&threadId, NULL, DoEatPhilosopher, options);

        struct timespec twb = RandomTime(1, 4);
        printf("[pid: %lu, philosopherId: %d, i: %d] Задержка "
               "перед отправкой следующего %lf сек.\n",
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