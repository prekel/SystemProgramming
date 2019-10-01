#include <malloc.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#include "RealTimeTableState.h"
#include "Philosopher.h"
#include "Utils.h"
#include "EatPhilosopherOptions.h"

Philosopher* CreatePhilosopher(int id, Fork* leftFork, Fork* rightFork)
{
    Philosopher* pPhilosopher = (Philosopher*) malloc(sizeof(Philosopher));
    pPhilosopher->PhilosopherId = id;
    pPhilosopher->pLeftFork = leftFork;
    pPhilosopher->pRightFork = rightFork;
    pPhilosopher->IsEating = false;
    pPhilosopher->IsWaiting = false;
    pPhilosopher->IsThreadRunning = false;
    pPhilosopher->IsWaitingLeftFork = false;
    pPhilosopher->IsWaitingRightFork = false;

    pPhilosopher->OnGoingToEat = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));
    pthread_cond_init(pPhilosopher->OnGoingToEat, NULL);

    pPhilosopher->OnMustToStop = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));
    pthread_cond_init(pPhilosopher->OnMustToStop, NULL);

    return pPhilosopher;
}

void DestroyPhilosopher(Philosopher* pPhilosopher)
{
    pthread_cond_destroy(pPhilosopher->OnGoingToEat);
    free(pPhilosopher->OnGoingToEat);
    pthread_cond_destroy(pPhilosopher->OnMustToStop);
    free(pPhilosopher->OnMustToStop);
    free(pPhilosopher);
}

