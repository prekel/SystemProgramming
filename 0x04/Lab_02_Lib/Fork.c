#include <malloc.h>
#include <pthread.h>
#include <stdio.h>

#include "Fork.h"
#include "Log.h"
#include "Macro.h"

#define FILE_NAME "Fork"

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

void TakeOnFork(Fork* pFork, pthread_mutex_t* pMutex, sem_t* pArbitrator)
{
    //pthread_mutex_lock(pMutex);
    //pthread_mutex_unlock(pMutex);
    //sem_wait(pArbitrator);
    //pthread_mutex_lock(pMutex);
    pFork->IsInUse = true;


    Log(FILE_NAME, "Занятие вилки с номером %d", pFork->ForkId);

    //int semValue;
    //sem_getvalue(pArbitrator, &semValue);
    //if (semValue == 0)
    //{
    //    printf("[pid: %lu, philosopherId: %d] ожидание2\n",
     //          pthread_self(), pPh->PhilosopherId);
    //}
    //pthread_mutex_unlock(pMutex);
}

void TakeOffFork(Fork* pFork, pthread_mutex_t* pMutex, sem_t* pArbitrator)
{
    pFork->IsInUse = false;

    pthread_cond_signal(pFork->CondSignalOnRelease);


    Log(FILE_NAME, "Освобождение вилки с номером %d", pFork->ForkId);

    //printf("[pid: 0x%08lx, forkId: %d] Освобождение вилки\n", pthread_self(), pFork->ForkId);
}

void DestroyFork(Fork* pFork)
{
    pthread_cond_destroy(pFork->CondSignalOnRelease);
    free(pFork->CondSignalOnRelease);
    free(pFork);
}