#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdbool.h>

#include "Fork.h"

typedef struct
{
    int PhilosopherId;
    Fork* RightFork;
    Fork* LeftFork;
    bool IsEating;
} Philosopher;

typedef struct
{
    Philosopher* pPhilosopher;
    pthread_mutex_t* Mutex;
    struct timespec* durationEat;
} EatPhilosopherOptions;

Philosopher* CreatePhilosopher(int id, Fork* leftFork, Fork* rightFork);

void* DoEatPhilosopher(void* pEatThreadOptions);

void DestroyPhilosopher(Philosopher* pPhilosopher);

EatPhilosopherOptions*
CreateEatPhilosopherOptions(Philosopher* pPhilosopher, pthread_mutex_t* mutex,
                            struct timespec* durationEat);

void DestroyEatPhilosopherOptions(EatPhilosopherOptions* pOptions);


#endif // PHILOSOPHER_H
