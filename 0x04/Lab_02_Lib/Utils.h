#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdbool.h>

#include "Philosopher.h"

static const int MS_IN_S = 1000;
static const int NS_IN_MS = 1000000;
static const int NS_IN_S = 1000000000;

/*!
 *
 * \param min
 * \param max
 * \return
 */
int RandomInterval(int min, int max);

struct timespec RandomTimeS(int minSeconds, int maxSeconds);

struct timespec RandomTimeMs(int minMs, int maxMs);

double TimespecToDouble(struct timespec duration, bool isInfinityDuration);

struct timespec TimespecFromDouble(double seconds);

int SleepOrWaitSignal(pthread_cond_t* pCondOnWaitingEnding, struct timespec duration,
                      bool isInfinityDuration, pthread_mutex_t* pMutex);

#endif // UTILS_H
