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
    return pFork;
}

void DestroyFork(Fork* pFork)
{
    free(pFork);
}