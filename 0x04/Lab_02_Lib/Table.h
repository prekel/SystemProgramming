/// \file
/// \brief Стол
/// \details Стол, функции для его создания, уничтожения, старта потоков и отправки философов.

#ifndef TABLE_H
#define TABLE_H

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#include "Philosopher.h"
#include "Fork.h"

/// \struct Table
///
/// Стол.
typedef struct
{
    /// Число философов
    int PhilosophersCount;
    /// Массив философов
    Philosopher** ppPhilosophers;
    /// Массив вилок
    Fork** ppForks;
    /// Начата ли трапеза
    bool IsEatingStarted;
    /// Кончилась ли трапеза
    bool IsEatingEnded;
    /// Должна ли кончится трапеза
    bool IsEatingMustEnd;
    /// Главный мьютекс
    pthread_mutex_t* pMutex;

    sem_t* pArbitrator;
} Table;

/// Инициализирует новый экземпляр стола. Требуется очистка с помощью DestroyTable.
///
/// \param philosophersCount Число философов.
/// \param minDurationEatMs Нижняя граница случайного времени для приёма пищи.
/// \param maxDurationEatMs Верхняя граница случайного времени для приёма пищи.
/// \param isInfinityDuration Бесконечен ли приём пищи.
/// \return Указатель на новый стол.
Table* CreateTable(int philosophersCount, int minDurationEatMs, int maxDurationEatMs,
            bool isInfinityDuration);

/// Запускиет все потоки философов.
///
/// \param pTable Указатель на стол.
void StartAllThreads(Table* pTable);

/// Уничтожает стол.
///
/// \param pTable Указатель на стол.
void DestroyTable(Table* pTable);

#endif // TABLE_H
