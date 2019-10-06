/// \file
/// \brief Вилка
/// \details Вилка, функции для её создания, уничтожения и взаимодействия

#ifndef FORK_H
#define FORK_H

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

/// \struct Fork
///
/// Вилка.
typedef struct
{
    int ForkId;
    bool IsInUse;
    pthread_cond_t* CondSignalOnRelease;
} Fork;

Fork* CreateFork(int id);

void TakeOnFork(Fork* pFork, pthread_mutex_t* pMutex, sem_t* pArbitrator);

void TakeOffFork(Fork* pFork, pthread_mutex_t* pMutex, sem_t* pArbitrator);

void DestroyFork(Fork* pFork);

#endif // FORK_H
