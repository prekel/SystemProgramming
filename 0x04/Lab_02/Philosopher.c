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
    pPhilosopher->IsWaiting = false;
    return pPhilosopher;
}

void* DoEatPhilosopher(void* pEatThreadOptions)
{
    EatPhilosopherOptions* pEatOptions = (EatPhilosopherOptions*) pEatThreadOptions;

    Philosopher* ph = pEatOptions->pPhilosopher;
    struct timespec* durationEat = pEatOptions->durationEat;
    pthread_mutex_t* mutex = pEatOptions->Mutex;

    printf("[pid: %lu, philosopherId: %d] Пришёл есть\n",
            pthread_self(),
           ph->PhilosopherId);
    pthread_mutex_lock(mutex);
    if (ph->LeftFork->IsInUse == false &&
        ph->RightFork->IsInUse == false)
    {
        printf("[pid: %lu, philosopherId: %d] Вилки свободны, "
               "начинает есть %lf сек.\n", pthread_self(), ph->PhilosopherId,
               TimespecToDouble(durationEat));
        ph->IsEating = true;
        ph->LeftFork->IsInUse = true;
        ph->RightFork->IsInUse = true;
        pthread_mutex_unlock(mutex);
        nanosleep(durationEat, NULL);
        pthread_mutex_lock(mutex);
        ph->LeftFork->IsInUse = false;
        pthread_cond_signal(ph->LeftFork->CondSignalOnRelease);
        ph->RightFork->IsInUse = false;
        pthread_cond_signal(ph->RightFork->CondSignalOnRelease);
        ph->IsEating = false;
        printf("[pid: %lu, philosopherId: %d] Поел, уходит\n",
                pthread_self(), ph->PhilosopherId);
        pthread_mutex_unlock(mutex);
    }
    else
    {
        ph->IsWaiting = true;

        if (ph->LeftFork->IsInUse)
        {
            printf("[pid: %lu, philosopherId: %d] Левая вилка несвободна, ожидание\n",
                   pthread_self(), ph->PhilosopherId);

            pthread_cond_wait(ph->LeftFork->CondSignalOnRelease, mutex);

            printf("[pid: %lu, philosopherId: %d] Занятие левой вилки\n",
                   pthread_self(), ph->PhilosopherId);
            ph->LeftFork->IsInUse = true;
        }

        if (ph->RightFork->IsInUse)
        {
            printf("[pid: %lu, philosopherId: %d] Правая вилка несвободна, ожидание\n",
                   pthread_self(), ph->PhilosopherId);

            pthread_cond_wait(ph->RightFork->CondSignalOnRelease, mutex);

            printf("[pid: %lu, philosopherId: %d] Занятие правой вилки\n",
                   pthread_self(), ph->PhilosopherId);
            ph->RightFork->IsInUse = true;
        }

        printf("[pid: %lu, philosopherId: %d] Начинает есть после ожидания\n",
               pthread_self(), ph->PhilosopherId);
        ph->IsWaiting = false;
        ph->IsEating = true;

        pthread_mutex_unlock(mutex);
        nanosleep(durationEat, NULL);
        pthread_mutex_lock(mutex);

        ph->LeftFork->IsInUse = false;
        pthread_cond_signal(ph->LeftFork->CondSignalOnRelease);
        ph->RightFork->IsInUse = false;
        pthread_cond_signal(ph->RightFork->CondSignalOnRelease);

        ph->IsEating = false;

        printf("[pid: %lu, philosopherId: %d] Поел после ожидания, уходит\n",
               pthread_self(), ph->PhilosopherId);
        pthread_mutex_unlock(mutex);
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
