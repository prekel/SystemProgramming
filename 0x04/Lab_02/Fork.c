#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Fork.h"

Fork* CreateFork(int id)
{
    Fork* pFork = (Fork*) malloc(sizeof(Fork));
    pFork->ForkId = id;
    pFork->IsInUse = false;
    pFork->CondSignalOnRelease = (pthread_cond_t*) malloc(
            sizeof(pthread_cond_t));
    pthread_cond_init(pFork->CondSignalOnRelease, NULL);
    return pFork;
}

void DestroyFork(Fork* pFork)
{
    pthread_cond_destroy(pFork->CondSignalOnRelease);
    free(pFork);
}