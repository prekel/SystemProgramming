#include "Fork.h"

#include "malloc.h"

Fork* CreateFork(int id)
{
    Fork* pFork = (Fork*) malloc(sizeof(Fork));
    pFork->ForkId = id;
    return pFork;
}

void DestroyFork(Fork* pFork)
{
    free(pFork);
}