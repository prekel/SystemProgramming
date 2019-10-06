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

Philosopher*
CreatePhilosopher(int id, Fork* leftFork, Fork* rightFork, int minDurationEatMs,
                  int maxDurationEatMs, bool isInfinityDuration)
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

//    pPhilosopher->pCondOnGoingToEat = (pthread_cond_t*)malloc(
//            sizeof(pthread_cond_t));
//    FAILURE_IF_NULLPTR(pPhilosopher->pCondOnGoingToEat);
//    pthread_cond_init(pPhilosopher->pCondOnGoingToEat, NULL);
//
//    pPhilosopher->pCondOnWaitingEnding = (pthread_cond_t*)malloc(
//            sizeof(pthread_cond_t));
//    FAILURE_IF_NULLPTR(pPhilosopher->pCondOnWaitingEnding);
//    pthread_cond_init(pPhilosopher->pCondOnWaitingEnding, NULL);

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

