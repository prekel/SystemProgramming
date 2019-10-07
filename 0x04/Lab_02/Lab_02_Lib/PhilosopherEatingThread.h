/// \file
/// \brief Поток философа
/// \details Поток философа, его конфигурация, функции для её создания уничтожения и тд.

#ifndef PHILOSOPHEREATINGTHREAD_H
#define PHILOSOPHEREATINGTHREAD_H

#include <pthread.h>
#include <semaphore.h>

#include "Table.h"
#include "Philosopher.h"

/// \struct PhilosopherEatingThreadOptions
///
/// Параметры запуска потока PhilosopherEatingThread.
typedef struct
{
    /// Указатель на стол
    Table* pTable;
    /// Указатель на философа
    Philosopher* pPhilosopher;
    /// Указатель на главный мьютекс
    pthread_mutex_t* pMutex;
} PhilosopherEatingThreadOptions;

/// Создаёт параметры запуска потока PhilosopherEatingThread.
/// Требуется очистка с помощью DestroyPhilosopherEatingThreadOptions.
///
/// \param pTable Указатель на стол.
/// \param pPhilosopher Указатель на философа.
/// \param pMutex Указатель на глаынй мьютекс.
/// \return Указатель на созданные параметры запуска.
PhilosopherEatingThreadOptions* CreatePhilosopherEatingThreadOptions(
        Table* pTable, Philosopher* pPhilosopher, pthread_mutex_t* pMutex);

/// Уничтожает параметры запуска потока PhilosopherEatingThread.
///
/// \param pOptions Указатель на параметры запуска потока.
void DestroyPhilosopherEatingThreadOptions(
        PhilosopherEatingThreadOptions* pOptions);

void* PhilosopherEatingThread(void* pEatThreadOptions);

#endif //PHILOSOPHEREATINGTHREAD_H
