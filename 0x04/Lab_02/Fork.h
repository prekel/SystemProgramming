#ifndef FORK_H
#define FORK_H

#include <stdbool.h>
#include <pthread.h>

typedef struct
{
    int ForkId;
    bool IsInUse;
    pthread_cond_t* CondSignalOnRelease;
} Fork;

Fork* CreateFork(int id);

void DestroyFork(Fork* pFork);

#endif // FORK_H
