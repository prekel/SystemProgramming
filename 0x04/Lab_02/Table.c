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
    pTable->Forks = (Fork**) malloc(PHILOSOPHERS_COUNT * sizeof(Fork*));
    for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    {
        pTable->Forks[i] = CreateFork(i + 1);
    }

    pTable->Philosophers = (Philosopher**) malloc(
            PHILOSOPHERS_COUNT * sizeof(Philosopher*));

    for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    {
        Fork* lFork = pTable->Forks[i == 0 ? PHILOSOPHERS_COUNT - 1 : i - 1];
        pTable->Philosophers[i] =
                CreatePhilosopher(i + 1, lFork, pTable->Forks[i]);
    }

    pTable->IsEatingStarted = false;
    pTable->IsEatingEnded = false;

    return pTable;
}

void DoEatAll1(Table* pTable)
{
    srand(time(NULL));
    pTable->IsEatingStarted = true;

    pthread_mutex_init(&pTable->Mutex, NULL);

    //for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    for (int i = 0; i < 20000000; i++)
    {
        //int a = rand() % 10 + 1;
        //int a = ;
        int c = rand() % PHILOSOPHERS_COUNT;
        //struct timespec tw = {a, 0};
        struct timespec tw = RandomTime(10, 20);

        Philosopher* ph = pTable->Philosophers[c];

        pthread_mutex_lock(&pTable->Mutex);
        if (ph->IsEating == true)
        {
            printf("[pid: %lu, philosopherId: %d, i: %d] Уже ест\n",
                   pthread_self(), ph->PhilosopherId, i);
            pthread_mutex_unlock(&pTable->Mutex);
            continue;
        }
        pthread_mutex_unlock(&pTable->Mutex);
        pthread_mutex_lock(&pTable->Mutex);
        if (ph->IsWaiting == true)
        {
            printf("[pid: %lu, philosopherId: %d, i: %d] Уже ожидает\n",
                   pthread_self(), ph->PhilosopherId, i);
            pthread_mutex_unlock(&pTable->Mutex);
            continue;
        }
        pthread_mutex_unlock(&pTable->Mutex);

        EatPhilosopherOptions* options
                = CreateEatPhilosopherOptions(ph, &pTable->Mutex, &tw);

        pthread_t threadId;

        printf("[pid: %lu, philosopherId: %d, i: %d] Идёт "
               "есть\n",
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
        DestroyFork(pTable->Forks[i]);
        DestroyPhilosopher(pTable->Philosophers[i]);
    }
    free(pTable->Forks);
    free(pTable->Philosophers);
    free(pTable);
}