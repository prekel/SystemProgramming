/// \file
/// \brief Философ
/// \details Философ, функции для создания, уничтожения итд.

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#include "Fork.h"

/// \struct Philosopher
///
/// Философ.
typedef struct
{
    /// Номер философа
    int PhilosopherId;
    /// Указатель на правую филку
    Fork* pRightFork;
    /// Указатель на левую вилку
    Fork* pLeftFork;
    /// Ест ли философ
    bool IsEating;
    /// Ожидает ли философ
    bool IsWaiting;
    /// Запущен ли поток философа
    bool IsThreadRunning;
    /// Идентификатор потока философа
    pthread_t pThread;
    /// Указатель на семафор, сигнализирующий о том, что нужно начать есть
    sem_t* pSemOnGoingToEat;
    /// Указатель на семафор, сигнализирующий что требуется перестать есть
    /// или ждать
    sem_t* pSemOnWaitingEnding;
    /// Ждёт ли философ левую вилку.
    bool IsWaitingLeftFork;
    /// Ждёт ли философ правую вилку.
    bool IsWaitingRightFork;
    /// Нижняя граница случайного времени приёма пищи в миллисекундах
    int MinDurationEatMs;
    /// Верхняя граница случайного времени приёма пищи в миллисекундах
    int MaxDurationEatMs;
    /// Бесконечен ли приём пищи
    bool IsInfinityDuration;
} Philosopher;

/// Создаёт философа. Требудется очистка с помощью DestroyPhilosopher.
///
/// \param id Номер философа.
/// \param leftFork Указатель на левую вилку.
/// \param rightFork Указатель на правую вилку.
/// \param minDurationEatMs Нижняя граница случайного времени приёма пищи
/// в миллисекундах.
/// \param maxDurationEatMs Верхняя граница случайного времени приёма пищи
/// в миллисекундах.
/// \param isInfinityDuration Бесконечен ли приём пищи.
/// \return Указатель на созданного филисофа.
Philosopher* CreatePhilosopher(int id, Fork* leftFork, Fork* rightFork,
                               int minDurationEatMs, int maxDurationEatMs,
                               bool isInfinityDuration);

/// Уничтожает философа.
///
/// \param pPhilosopher Указатель на уничтожаемого философа.
void DestroyPhilosopher(Philosopher* pPhilosopher);

/// Заставляет философа перестать есть или ожидать свободных вилок.
/// Мьютекс должен быть разблокированным.
///
/// \param pPhilosopher Указатель на философа.
/// \param pMutex Указатель на главный мьютекс.
/// \return 0 если удачно прервано, 1 если философ ни ест, ни ожидает.
int InterruptEating(Philosopher* pPhilosopher, pthread_mutex_t* pMutex);

#endif //PHILOSOPHER_H
