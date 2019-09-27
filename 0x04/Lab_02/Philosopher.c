#include <malloc.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>

#include "Philosopher.h"

Philosopher* CreatePhilosopher(int id, Fork* leftFork, Fork* rightFork)
{
    Philosopher* pPhilosopher = (Philosopher*) malloc(sizeof(Philosopher));
    pPhilosopher->PhilosopherId = id;
    pPhilosopher->LeftFork = leftFork;
    pPhilosopher->RightFork = rightFork;
    return pPhilosopher;
}

void DoEatPhilosopher(Philosopher* pPhilosopher, struct timespec* durationEat)
{
    printf("[pid: %lu, philosopherId: %d] Пришёл есть\n", pthread_self(),
           pPhilosopher->PhilosopherId);
    if (pPhilosopher->LeftFork->IsInUse == false &&
        pPhilosopher->RightFork->IsInUse == false)
    {
        printf("[pid: %lu, philosopherId: %d] Вилки свободны, начинает "
               "есть\n", pthread_self(), pPhilosopher->PhilosopherId);
        pPhilosopher->LeftFork->IsInUse = true;
        pPhilosopher->RightFork->IsInUse = true;
        nanosleep(durationEat, NULL);
        pPhilosopher->LeftFork->IsInUse = false;
        pPhilosopher->RightFork->IsInUse = false;
        printf("[pid: %lu, philosopherId: %d] Поел, уходит "
               "есть\n", pthread_self(), pPhilosopher->PhilosopherId);
    }
    else
    {
        printf("[pid: %lu, philosopherId: %d] Вилки несвободны, уходит\n",
               pthread_self(), pPhilosopher->PhilosopherId);
    }
}

void DestroyPhilosopher(Philosopher* pPhilosopher)
{
    free(pPhilosopher);
}