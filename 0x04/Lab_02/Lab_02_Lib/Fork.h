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

/// Создаёт вилку. Требуется очистка с помощью DestroyFork.
///
/// \param id Номер вилки.
/// \return Указатель на созданную вилку.
Fork* CreateFork(int id);

/// Взять вилку. Главный мьютекс должен быть заблокирован.
///
/// \param pFork Указатель на вилку, которую нужно взять.
void TakeOnFork(Fork* pFork);

/// Положить вилку. Главный мьютекс должен быть заблокирован.
///
/// \param pFork Указатель на вилку, которую требуется положить.
void TakeOffFork(Fork* pFork);

/// Уничтожает вилку.
///
/// \param pFork Указатель на вилку, которую требудется уничтожить.
void DestroyFork(Fork* pFork);

#endif // FORK_H
