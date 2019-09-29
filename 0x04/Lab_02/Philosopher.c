#include <malloc.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#include "Philosopher.h"
#include "Utils.h"

Philosopher* CreatePhilosopher(int id, Fork* leftFork, Fork* rightFork)
{
    Philosopher* pPhilosopher = (Philosopher*) malloc(sizeof(Philosopher));
    pPhilosopher->PhilosopherId = id;
    pPhilosopher->pLeftFork = leftFork;
    pPhilosopher->pRightFork = rightFork;
    pPhilosopher->IsEating = false;
    pPhilosopher->IsWaiting = false;
    return pPhilosopher;
}

void* DoEatPhilosopher(void* pEatThreadOptions)
{
    EatPhilosopherOptions* pEatOptions = (EatPhilosopherOptions*) pEatThreadOptions;

    Philosopher* pPh = pEatOptions->pPhilosopher;
    struct timespec* pDurationEat = pEatOptions->pDurationEat;
    pthread_mutex_t* pMutex = pEatOptions->pMutex;
    sem_t* pArbitrator = pEatOptions->pArbitrator;

    printf("[pid: %lu, philosopherId: %d] Пришёл есть\n",
           pthread_self(),
           pPh->PhilosopherId);
    pthread_mutex_lock(pMutex);
    if (pPh->pLeftFork->IsInUse == false &&
        pPh->pRightFork->IsInUse == false)
    {
        printf("[pid: %lu, philosopherId: %d] Вилки свободны, "
               "начинает есть %lf сек.\n", pthread_self(), pPh->PhilosopherId,
               TimespecToDouble(pDurationEat));

        pPh->IsEating = true;

        int semValue;
        sem_getvalue(pArbitrator, &semValue);
        if (semValue == 0)
        {
            printf("[pid: %lu, philosopherId: %d] ожидание1\n",
                   pthread_self(), pPh->PhilosopherId);
        }
        pthread_mutex_unlock(pMutex);
        sem_wait(pArbitrator);
        pthread_mutex_lock(pMutex);
        pPh->pLeftFork->IsInUse = true;

        sem_getvalue(pArbitrator, &semValue);
        if (semValue == 0)
        {
            printf("[pid: %lu, philosopherId: %d] ожидание2\n",
                   pthread_self(), pPh->PhilosopherId);
        }
        pthread_mutex_unlock(pMutex);
        sem_wait(pArbitrator);
        pthread_mutex_lock(pMutex);
        pPh->pRightFork->IsInUse = true;

        pthread_mutex_unlock(pMutex);
        printf("[pid: %lu, philosopherId: %d] Начал есть\n",
                pthread_self(), pPh->PhilosopherId);
        nanosleep(pDurationEat, NULL);
        printf("[pid: %lu, philosopherId: %d] Закончил есть\n",
               pthread_self(), pPh->PhilosopherId);
        pthread_mutex_lock(pMutex);

        pPh->pLeftFork->IsInUse = false;
        pthread_cond_signal(pPh->pLeftFork->CondSignalOnRelease);
        sem_post(pArbitrator);

        pPh->pRightFork->IsInUse = false;
        pthread_cond_signal(pPh->pRightFork->CondSignalOnRelease);
        sem_post(pArbitrator);

        pPh->IsEating = false;

        printf("[pid: %lu, philosopherId: %d] Поел, уходит\n",
               pthread_self(), pPh->PhilosopherId);
        pthread_mutex_unlock(pMutex);
    }
    else
    {
        pPh->IsWaiting = true;

        if (pPh->pLeftFork->IsInUse)
        {
            int semValue;
            sem_getvalue(pArbitrator, &semValue);
            if (semValue == 0)
            {
                printf("[pid: %lu, philosopherId: %d] Четыре вилки занято, ожидание\n",
                       pthread_self(), pPh->PhilosopherId);
            }
            pthread_mutex_unlock(pMutex);
            sem_wait(pArbitrator);
            pthread_mutex_lock(pMutex);

            printf("[pid: %lu, philosopherId: %d] Левая вилка несвободна, ожидание\n",
                   pthread_self(), pPh->PhilosopherId);

            pthread_cond_wait(pPh->pLeftFork->CondSignalOnRelease, pMutex);

            printf("[pid: %lu, philosopherId: %d] Занятие левой вилки\n",
                   pthread_self(), pPh->PhilosopherId);

            pPh->pLeftFork->IsInUse = true;
        }

        if (pPh->pRightFork->IsInUse)
        {
            int semValue;
            sem_getvalue(pArbitrator, &semValue);
            if (semValue == 0)
            {
                printf("[pid: %lu, philosopherId: %d] Четыре вилки занято, ожидание\n",
                       pthread_self(), pPh->PhilosopherId);
            }
            pthread_mutex_unlock(pMutex);
            sem_wait(pArbitrator);
            pthread_mutex_lock(pMutex);

            printf("[pid: %lu, philosopherId: %d] Правая вилка несвободна, ожидание\n",
                   pthread_self(), pPh->PhilosopherId);

            pthread_cond_wait(pPh->pRightFork->CondSignalOnRelease, pMutex);

            printf("[pid: %lu, philosopherId: %d] Занятие правой вилки\n",
                   pthread_self(), pPh->PhilosopherId);

            pPh->pRightFork->IsInUse = true;
        }

        printf("[pid: %lu, philosopherId: %d] Начинает есть после ожидания\n",
               pthread_self(), pPh->PhilosopherId);
        pPh->IsWaiting = false;
        pPh->IsEating = true;

        pthread_mutex_unlock(pMutex);
        printf("[pid: %lu, philosopherId: %d] Начал есть\n",
               pthread_self(), pPh->PhilosopherId);
        nanosleep(pDurationEat, NULL);
        printf("[pid: %lu, philosopherId: %d] Закончил есть\n",
               pthread_self(), pPh->PhilosopherId);
        pthread_mutex_lock(pMutex);

        sem_post(pArbitrator);
        pPh->pLeftFork->IsInUse = false;
        pthread_cond_signal(pPh->pLeftFork->CondSignalOnRelease);
        sem_post(pArbitrator);
        pPh->pRightFork->IsInUse = false;
        pthread_cond_signal(pPh->pRightFork->CondSignalOnRelease);

        pPh->IsEating = false;

        printf("[pid: %lu, philosopherId: %d] Поел после ожидания, уходит\n",
               pthread_self(), pPh->PhilosopherId);
        pthread_mutex_unlock(pMutex);
    }

    return NULL;
}

void DestroyPhilosopher(Philosopher* pPhilosopher)
{
    free(pPhilosopher);
}

EatPhilosopherOptions*
CreateEatPhilosopherOptions(Philosopher* pPhilosopher, pthread_mutex_t* mutex,
                            struct timespec* durationEat, sem_t* pArbitrator)
{
    EatPhilosopherOptions* pOptions = (EatPhilosopherOptions*)malloc(
            sizeof(EatPhilosopherOptions));
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
