#include "Logger.h"
#include <limits.h>
#include <signal.h>
#include <errno.h>
#include <malloc.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#include "RealTimeTableStateThread.h"
#include "Philosopher.h"
#include "Utils.h"
#include "PhilosopherEatingThread.h"
#include "Macro.h"

Philosopher* CreatePhilosopher(int id, Fork* leftFork, Fork* rightFork, int minDurationEatMs, int maxDurationEatMs, bool isInfinityDuration)
{
    Philosopher* pPhilosopher = (Philosopher*) malloc(sizeof(Philosopher));
    FAILURE_IF_NULLPTR(pPhilosopher);

    pPhilosopher->PhilosopherId = id;
    pPhilosopher->pLeftFork = leftFork;
    pPhilosopher->pRightFork = rightFork;

    pPhilosopher->IsEating = false;
    pPhilosopher->IsWaiting = false;
    pPhilosopher->IsThreadRunning = false;
    pPhilosopher->IsWaitingLeftFork = false;
    pPhilosopher->IsWaitingRightFork = false;

    pPhilosopher->MinDurationEatMs = minDurationEatMs;
    pPhilosopher->MaxDurationEatMs = maxDurationEatMs;
    pPhilosopher->IsInfinityDuration = isInfinityDuration;


    pPhilosopher->pSemOnGoingToEat = (sem_t*) malloc(
            sizeof(sem_t));
    FAILURE_IF_NULLPTR(pPhilosopher->pSemOnGoingToEat);
    sem_init(pPhilosopher->pSemOnGoingToEat, 0, 0);

    pPhilosopher->pSemOnWaitingEnding = (sem_t*) malloc(
            sizeof(sem_t));
    FAILURE_IF_NULLPTR(pPhilosopher->pSemOnWaitingEnding);
    sem_init(pPhilosopher->pSemOnWaitingEnding, 0, 0);

    return pPhilosopher;
}

void DestroyPhilosopher(Philosopher* pPhilosopher)
{
    sem_destroy(pPhilosopher->pSemOnGoingToEat);
    free(pPhilosopher->pSemOnGoingToEat);
    sem_destroy(pPhilosopher->pSemOnWaitingEnding);
    free(pPhilosopher->pSemOnWaitingEnding);
//    pthread_cond_destroy(pPhilosopher->pCondOnGoingToEat);
//    free(pPhilosopher->pCondOnGoingToEat);
//    pthread_cond_destroy(pPhilosopher->pCondOnWaitingEnding);
//    free(pPhilosopher->pCondOnWaitingEnding);
    free(pPhilosopher);
}

int InterruptEating(Philosopher* pPhilosopher, pthread_mutex_t* pMutex)
{
    LOG("Попытка прервать приём пищи философа с номером %d",
        pPhilosopher->PhilosopherId);

    pthread_mutex_lock(pMutex);
    if (pPhilosopher->IsEating)
    {
        LOG("Приём пищи философа с номером %d прерван",
            pPhilosopher->PhilosopherId);
        //pthread_cond_signal(pPhilosopher->pCondOnWaitingEnding);
        sem_post(pPhilosopher->pSemOnWaitingEnding);
        pthread_mutex_unlock(pMutex);
        return 0;
    }
    else if (pPhilosopher->IsWaitingLeftFork)
    {
        LOG("Ожидание левой вилки философом с номером %d прервано",
            pPhilosopher->PhilosopherId);
        pthread_cond_signal(pPhilosopher->pLeftFork->CondSignalOnRelease);
        pthread_mutex_unlock(pMutex);
        return 0;
    }
    else if (pPhilosopher->IsWaitingRightFork)
    {
        LOG("Ожидание правой вилки философом с номером %d прервано",
            pPhilosopher->PhilosopherId);
        pthread_cond_signal(pPhilosopher->pRightFork->CondSignalOnRelease);
        pthread_mutex_unlock(pMutex);
        return 0;
    }

    LOG("Философ с номером %d не ест", pPhilosopher->PhilosopherId);
    pthread_mutex_unlock(pMutex);

    return 1;
}
