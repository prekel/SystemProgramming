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
CreatePhilosopher(int id, Fork* leftFork, Fork* rightFork, int minDurationEat,
                  int maxDurationEat, bool isInfinityDuration)
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

    pPhilosopher->pSemOnGoingToEat = (sem_t*)malloc(sizeof(sem_t));
    FAILURE_IF_NULLPTR(pPhilosopher->pSemOnGoingToEat);
    sem_init(pPhilosopher->pSemOnGoingToEat, 0, 0);

    pPhilosopher->pSemOnInfinityWaitingEnding = (sem_t*)malloc(sizeof(sem_t));
    FAILURE_IF_NULLPTR(pPhilosopher->pSemOnInfinityWaitingEnding);
    sem_init(pPhilosopher->pSemOnInfinityWaitingEnding, 0, 0);

    pPhilosopher->MinDurationEat = minDurationEat;
    pPhilosopher->MaxDurationEat = maxDurationEat;
    pPhilosopher->IsInfinityDuration = isInfinityDuration;

//    pPhilosopher->OnGoingToEat = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));
//    pthread_cond_init(pPhilosopher->OnGoingToEat, NULL);
//
//    pPhilosopher->OnMustToStop = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));
//    pthread_cond_init(pPhilosopher->OnMustToStop, NULL);

    return pPhilosopher;
}

void DestroyPhilosopher(Philosopher* pPhilosopher)
{
    sem_destroy(pPhilosopher->pSemOnGoingToEat);
    free(pPhilosopher->pSemOnGoingToEat);
    sem_destroy(pPhilosopher->pSemOnInfinityWaitingEnding);
    free(pPhilosopher->pSemOnInfinityWaitingEnding);
//    pthread_cond_destroy(pPhilosopher->OnGoingToEat);
//    free(pPhilosopher->OnGoingToEat);
//    pthread_cond_destroy(pPhilosopher->OnMustToStop);
//    free(pPhilosopher->OnMustToStop);
    free(pPhilosopher);
}

