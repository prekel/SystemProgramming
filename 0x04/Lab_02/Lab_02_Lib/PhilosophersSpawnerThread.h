/// \file
/// \brief Поток, посылающий философов есть
/// \details Поток, посылающий философов есть, параметры его запуска, итд.

#ifndef PHILOSOPHERSSPAWNERTHREAD_H
#define PHILOSOPHERSSPAWNERTHREAD_H

#include <stdbool.h>

#include "Table.h"

/// \struct
///
/// Параметры запуска потока PhilosophersSpawnerThread.
typedef struct
{
    Table* pTable;
    int MinSendIntervalDuration;
    int MaxSendIntervalDuration;
    pthread_mutex_t* pMutex;
    sem_t* OnSemQuit;
} PhilosophersSpawnerThreadOptions;

/// Создаёт параметры запуска потока PhilosophersSpawnerThread. Требуется
/// очистка с помощью DestroyPhilosophersSpawnerThreadOptions.
///
/// \param pTable Указатель на стол.
/// \param minSendIntervalDuration Нижняя граница случайного времени в
/// миллисекундах между отправками.
/// \param maxSendIntervalDuration Верхняя граница случайного времени в
/// миллисекундах между отправками.
/// \return Указатель на созданные параметры.
PhilosophersSpawnerThreadOptions* CreatePhilosophersSpawnerThreadOptions(
        Table* pTable,
        int minSendIntervalDuration,
        int maxSendIntervalDuration);

/// Уничтожает параметры запуска потока PhilosophersSpawnerThread.
///
/// \param pOptions Указатель на параметры запуска потока.
void DestroyPhilosophersSpawnerThreadOptions(
        PhilosophersSpawnerThreadOptions* pOptions);

/// Посылает философа есть.
///
/// \param pTable Указатель на стол.
/// \param pPhilosopher Указатель на философа.
/// \return 1 если философ уже есть или ожидает, 0 если свободен и
/// успешно отправлен.
int SpawnPhilosopher(Table* pTable, Philosopher* pPhilosopher);

///Ц
///
/// \param pAutoEatThreadOptions
/// \return
void* PhilosophersSpawnerThread(void* pAutoEatThreadOptions);

#endif //PHILOSOPHERSSPAWNERTHREAD_H
