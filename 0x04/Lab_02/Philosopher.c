#include <malloc.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>

#include "Philosopher.h"
#include "Utils.h"

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
    pthread_mutex_t* mutex = pEatOptions->Mutex;

    printf("[clock: %ld][pid: %lu, philosopherId: %d] Пришёл есть\n", clock
    (),
            pthread_self(),
           ph->PhilosopherId);
    //pthread_mutex_lock(mutex);
    if (ph->LeftFork->IsInUse == false &&
        ph->RightFork->IsInUse == false)
    {
        printf("[clock: %ld][pid: %lu, philosopherId: %d] Вилки свободны, "
               "начинает "
               "есть %lf сек.\n", clock(), pthread_self(), ph->PhilosopherId,
               TimespecToDouble(durationEat));
        ph->IsEating = true;
        ph->LeftFork->IsInUse = true;
        ph->RightFork->IsInUse = true;
        //pthread_mutex_unlock(mutex);
        nanosleep(durationEat, NULL);
        //pthread_mutex_lock(mutex);
        ph->LeftFork->IsInUse = false;
        ph->RightFork->IsInUse = false;
        ph->IsEating = false;
        printf("[clock: %ld][pid: %lu, philosopherId: %d] Поел, уходит\n",
                clock(),
                pthread_self(), ph->PhilosopherId);
        //pthread_mutex_unlock(mutex);
    }
    else
    {
        printf("[clock: %ld][pid: %lu, philosopherId: %d] Вилки несвободны,"
               " уходит\n", clock(),
               pthread_self(), ph->PhilosopherId);
    }

    return NULL;
}

void DestroyPhilosopher(Philosopher* pPhilosopher)
{
    free(pPhilosopher);
}

EatPhilosopherOptions* CreateEatPhilosopherOptions(Philosopher* pPhilosopher, pthread_mutex_t* mutex, struct timespec* durationEat)
{
    EatPhilosopherOptions* pEatPhilosopherOptions = (EatPhilosopherOptions*)malloc(
            sizeof(EatPhilosopherOptions));
    pEatPhilosopherOptions->pPhilosopher = pPhilosopher;
    pEatPhilosopherOptions->durationEat = durationEat;
    pEatPhilosopherOptions->Mutex = mutex;
    return pEatPhilosopherOptions;
}

void DestroyEatPhilosopherOptions(EatPhilosopherOptions* pOptions)
{
    free(pOptions);
}
