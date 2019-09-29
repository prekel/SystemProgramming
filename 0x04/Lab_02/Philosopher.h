#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdbool.h>

#include "Fork.h"

typedef struct
{
    int PhilosopherId;
    Fork* pRightFork;
    Fork* pLeftFork;
    bool IsEating;
    bool IsWaiting;
} Philosopher;

typedef struct
{
    Philosopher* pPhilosopher;
    pthread_mutex_t* pMutex;
    sem_t* pArbitrator;
    struct timespec* pDurationEat;
} EatPhilosopherOptions;

Philosopher* CreatePhilosopher(int id, Fork* leftFork, Fork* rightFork);

void* DoEatPhilosopher(void* pEatThreadOptions);

void DestroyPhilosopher(Philosopher* pPhilosopher);

EatPhilosopherOptions*
CreateEatPhilosopherOptions(Philosopher* pPhilosopher, pthread_mutex_t* mutex,
                            struct timespec* durationEat, sem_t* pArbitrator);

void DestroyEatPhilosopherOptions(EatPhilosopherOptions* pOptions);


#endif // PHILOSOPHER_H
