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
    pPhilosopher->IsEating = false;
    return pPhilosopher;
}

void* DoEatPhilosopher(void* pEatThreadOptions)
{
    EatPhilosopherOptions* pEatOptions = (EatPhilosopherOptions*) pEatThreadOptions;

    Philosopher* ph = pEatOptions->pPhilosopher;
    struct timespec* durationEat = pEatOptions->durationEat;

    printf("[pid: %lu, philosopherId: %d] Пришёл есть\n", pthread_self(),
           ph->PhilosopherId);
    if (ph->LeftFork->IsInUse == false &&
        ph->RightFork->IsInUse == false)
    {
        printf("[pid: %lu, philosopherId: %d] Вилки свободны, начинает "
               "есть %ld секунд\n", pthread_self(), ph->PhilosopherId,
               durationEat->tv_sec);
        ph->IsEating = true;
        ph->LeftFork->IsInUse = true;
        ph->RightFork->IsInUse = true;
        nanosleep(durationEat, NULL);
        ph->LeftFork->IsInUse = false;
        ph->RightFork->IsInUse = false;
        ph->IsEating = false;
        printf("[pid: %lu, philosopherId: %d] Поел, уходит\n",
                pthread_self(), ph->PhilosopherId);
    }
    else
    {
        printf("[pid: %lu, philosopherId: %d] Вилки несвободны, уходит\n",
               pthread_self(), ph->PhilosopherId);
    }

    return NULL;
}

void DestroyPhilosopher(Philosopher* pPhilosopher)
{
    free(pPhilosopher);
}

EatPhilosopherOptions* CreateEatPhilosopherOptions(Philosopher* pPhilosopher, struct timespec*
durationEat)
{
    EatPhilosopherOptions* pEatPhilosopherOptions = (EatPhilosopherOptions*)malloc(
            sizeof(EatPhilosopherOptions));
    pEatPhilosopherOptions->pPhilosopher = pPhilosopher;
    pEatPhilosopherOptions->durationEat = durationEat;
    return pEatPhilosopherOptions;
}

void DestroyEatPhilosopherOptions(EatPhilosopherOptions* pOptions)
{
    free(pOptions);
}
