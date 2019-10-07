/// \file
/// \brief Прочие функции
/// \details Прочие функции, такие как для генерации случайных чисел
/// или времени в интервале итд.

#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdbool.h>

#include "Philosopher.h"

/// Число миллисекунд в секундах
static const int MS_IN_S = 1000;
/// Число наносекунд в миллисекундах
static const int NS_IN_MS = 1000000;
/// Число наносекунд в секундах
static const int NS_IN_S = 1000000000;

/// Генерирует случайное число используя rand в полуинтервале [min, max).
/// Разность max - min не должна быть больше RAND_MAX и не меньше 0.
/// Если min == max, то возвращается min.
///
/// \param min Нижняя граница генеруремого случайного числа.
/// \param max Верхняя граница генеруремого случайного числа.
/// \return Случайное число.
int RandomInterval(int min, int max);

/// Генерирует случайное время используя rand в полуинтервале [minMs, maxMs).
/// Разность maxMs - minMs не должна быть больше RAND_MAX и не меньше 0.
/// Если minMs == maxMs, то возвращается minMs.
///
/// \param minMs Нижняя граница генерируемого случайного времени
/// в миллисекундах.
/// \param maxMs Верхняя граница генерируемого случайного времени
/// в миллисекундах.
/// \return Случайное время с точностью до наносекунды.
struct timespec RandomTimeMs(int minMs, int maxMs);

/// Переводит время в наносекундах в рациональное число секунд.
/// Если помечено, что время бесконечно, возвращается INFINITY.
///
/// \param time Время для перевода.
/// \param isInfinityTime Бесконечно ли время.
/// \return Время в секундах в рациональном виде.
double TimespecToDouble(struct timespec time, bool isInfinityTime);

/// Ожидает семафора до заданного времени.
///
/// \param pSemOnWaitingEnding Ожидаемый семафор.
/// \param duration Время ожидания.
/// \param isInfinityDuration Бесконечно ли время ожидания.
/// \return 0 если время закончилось быстрее, 1 если семафор быстрее времени.
int SleepOrWaitSem(sem_t* pSemOnWaitingEnding, struct timespec duration,
                   bool isInfinityDuration);

#endif //UTILS_H
