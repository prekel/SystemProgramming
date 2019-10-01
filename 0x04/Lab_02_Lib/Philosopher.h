#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdbool.h>

#include "Fork.h"

#define PHILOSOPHERS_COUNT 5

typedef struct
{
    int PhilosopherId;
    Fork* pRightFork;
    Fork* pLeftFork;
    bool IsEating;
    bool IsWaiting;
    bool IsThreadRunning;
    pthread_t pThread;
} Philosopher;

Philosopher* CreatePhilosopher(int id, Fork* leftFork, Fork* rightFork);

void DestroyPhilosopher(Philosopher* pPhilosopher);


#endif // PHILOSOPHER_H
