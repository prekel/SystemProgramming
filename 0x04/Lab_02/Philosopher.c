#include "Philosopher.h"

#include "malloc.h"

Philosopher* CreatePhilosopher(int id, Fork* leftFork, Fork* rightFork)
{
    Philosopher* pPhilosopher = (Philosopher*) malloc(sizeof(Philosopher));
    pPhilosopher->PhilosopherId = id;
    pPhilosopher->LeftFork = leftFork;
    pPhilosopher->RightFork = rightFork;
    return pPhilosopher;
}

void DestroyPhilosopher(Philosopher* pPhilosopher)
{
    free(pPhilosopher);
}