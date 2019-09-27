#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include "Fork.h"

typedef struct
{
    int PhilosopherId;
    Fork* RightFork;
    Fork* LeftFork;
} Philosopher;

typedef struct
{
    Philosopher* pPhilosopher;
    struct timespec* durationEat;
} EatPhilosopherOptions;


Philosopher* CreatePhilosopher(int id, Fork* leftFork, Fork* rightFork);

void DoEatPhilosopher(void* pEatThreadOptions);

void DestroyPhilosopher(Philosopher* pPhilosopher);

EatPhilosopherOptions* CreateEatPhilosopherOptions(Philosopher* pPhilosopher, struct timespec*
durationEat);

void DestroyEatPhilosopherOptions(EatPhilosopherOptions* pOptions);


#endif // PHILOSOPHER_H
