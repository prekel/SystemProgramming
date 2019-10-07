/// \file
/// \brief Поток, завершающий потоки философов
/// \details Поток, завершающий потоки философов, его параметры запуска итд.

#ifndef PHILOSOPHERSWAITERTHREAD_H
#define PHILOSOPHERSWAITERTHREAD_H

#include <pthread.h>

#include "Table.h"

/// \struct PhilosophersWaiterThreadOptions
///
/// Параметры запуска потока PhilosophersWaiterThread.
typedef struct
{
    /// Указатель на стол
    Table* pTable;
    /// Указатель на главный мьтекс
    pthread_mutex_t* pMutex;
} PhilosophersWaiterThreadOptions;

/// Создаёт параметры запуска потока PhilosophersWaiterThread. Требуется
/// очистка с помощью DestroyPhilosophersWaiterThreadOptions.
///
/// \param pTable Указатель на стол.
/// \return Указатель на созданные параметры запуска.
PhilosophersWaiterThreadOptions* CreatePhilosophersWaiterThreadOptions(
        Table* pTable);

/// Уничтожает параметры запуска потока.
///
/// \param pOptions Указатель на параметры запуска потока.
void DestroyPhilosophersWaiterThreadOptions
        (PhilosophersWaiterThreadOptions* pOptions);

/// Функция потока, завершающего потоки философов.
///
/// \param pPhilosophersWaiterThreadOptions Указатель на параметры запуска.
/// \return Указатель на параметры, с какими был запущен.
void* PhilosophersWaiterThread(void* pPhilosophersWaiterThreadOptions);

#endif //PHILOSOPHERSWAITERTHREAD_H
