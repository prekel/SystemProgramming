#ifndef FORK_H
#define FORK_H

#include <stdbool.h>

typedef struct
{
    int ForkId;
    bool IsInUse;
} Fork;

Fork* CreateFork(int id);

void DestroyFork(Fork* pFork);

#endif // FORK_H
