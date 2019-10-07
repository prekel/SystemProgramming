/// \file
/// \brief Реализация функций из Fork.h
/// \details Реализация функций из Fork.h.

#include <malloc.h>
#include <pthread.h>
#include <stdio.h>

#include "Fork.h"
#include "Logger.h"

Fork* CreateFork(int id)
{
    Fork* pFork = (Fork*) malloc(sizeof(Fork));
    FAILURE_IF_NULLPTR(pFork);

    pFork->ForkId = id;
    pFork->IsInUse = false;

    pFork->CondSignalOnRelease = (pthread_cond_t*) malloc(
            sizeof(pthread_cond_t));
    FAILURE_IF_NULLPTR(pFork->CondSignalOnRelease);
    pthread_cond_init(pFork->CondSignalOnRelease, NULL);

    return pFork;
}

void TakeOnFork(Fork* pFork)
{
    pFork->IsInUse = true;

    LOG("Занятие вилки с номером %d", pFork->ForkId);
}

void TakeOffFork(Fork* pFork)
{
    pFork->IsInUse = false;

    pthread_cond_signal(pFork->CondSignalOnRelease);

    LOG("Освобождение вилки с номером %d", pFork->ForkId);
}

void DestroyFork(Fork* pFork)
{
    pthread_cond_destroy(pFork->CondSignalOnRelease);
    free(pFork->CondSignalOnRelease);
    free(pFork);
}
