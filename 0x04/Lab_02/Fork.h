#ifndef FORK_H
#define FORK_H

typedef struct
{
    int ForkId;
} Fork;

Fork* CreateFork(int id);

void DestroyFork(Fork* pFork);

#endif // FORK_H
