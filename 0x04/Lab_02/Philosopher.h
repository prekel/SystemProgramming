#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include "Fork.h"

typedef struct
{
    int PhilosopherId;
    Fork* RightFork;
    Fork* LeftFork;
} Philosopher;

Philosopher* CreatePhilosopher(int id, Fork* leftFork, Fork* rightFork);

void DestroyPhilosopher(Philosopher* pPhilosopher);

#endif // PHILOSOPHER_H
