#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdbool.h>

#include "Fork.h"

//#define PHILOSOPHERS_COUNT 5

typedef struct
{
    int PhilosopherId;
    Fork* pRightFork;
    Fork* pLeftFork;
    bool IsEating;
    bool IsWaiting;
    bool IsThreadRunning;
    pthread_t pThread;
    //sem_t* pSemOnGoingToEat;
    //pthread_cond_t* pCondOnGoingToEat;
    sem_t* pSemOnGoingToEat;
    //sem_t* pSemOnInfinityWaitingEnding;
    //pthread_cond_t* pCondOnWaitingEnding;
    sem_t* pSemOnWaitingEnding;
    //pthread_cond_t* OnGoingToEat;
    //pthread_cond_t* OnMustToStop;
    bool IsWaitingLeftFork;
    bool IsWaitingRightFork;
    int MinDurationEatMs;
    int MaxDurationEatMs;
    bool IsInfinityDuration;
} Philosopher;

Philosopher*
CreatePhilosopher(int id, Fork* leftFork, Fork* rightFork, int minDurationEatMs,
                  int maxDurationEatMs, bool isInfinityDuration);

void DestroyPhilosopher(Philosopher* pPhilosopher);


#endif // PHILOSOPHER_H
