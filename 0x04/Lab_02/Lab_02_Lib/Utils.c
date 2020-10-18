/// \file
/// \brief Реализация функций из Utils.h
/// \details Реализация функций из Utils.h.

#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

#include "Utils.h"
#include "Logger.h"

int RandomInterval(int min, int max)
{
    assert(max >= min);
    assert(max - min <= RAND_MAX);

    if (min == max)
    {
        return min;
    }
    return rand() % (max - min) + min;
}

struct timespec RandomTimeMs(int minMs, int maxMs)
{
    assert(maxMs >= minMs);

    struct timespec tw;
    if (maxMs == minMs)
    {
        tw.tv_sec = minMs / MS_IN_S;
        tw.tv_nsec = minMs % MS_IN_S * NS_IN_MS;
    }
    else
    {
        int randomMs = RandomInterval(minMs, maxMs);

        tw.tv_sec = randomMs / MS_IN_S;

        tw.tv_nsec =
                randomMs % MS_IN_S * NS_IN_MS +
                RandomInterval(0, 1000) * MS_IN_S +
                RandomInterval(0, 1000);
    }
    return tw;
}

double TimespecToDouble(struct timespec duration, bool isInfinityTime)
{
    if (isInfinityTime)
    {
        return INFINITY;
    }
    return duration.tv_sec * 1.0 + duration.tv_nsec * 1.0 / NS_IN_S;
}

int SleepOrWaitSem(sem_t* pSemOnWaitingEnding, struct timespec duration,
                   bool isInfinityDuration)
{
    if (isInfinityDuration)
    {
        struct timespec infinityTime = {INT_MAX, NS_IN_S - 1};
        int timedwaitReturns = sem_timedwait(
                pSemOnWaitingEnding,
                &infinityTime);
        //LOG("sem_timedwait");
        //int timedwaitReturns = 1;
        return timedwaitReturns == 0;
    }
    else
    {
        struct timespec currentTime;
        clock_gettime(CLOCK_REALTIME, &currentTime);

        struct timespec endTime = {
                currentTime.tv_sec + duration.tv_sec,
                currentTime.tv_nsec + duration.tv_nsec};
        if (endTime.tv_nsec >= NS_IN_S)
        {
            endTime.tv_sec++;
            endTime.tv_nsec -= NS_IN_S;
        }

        int timedwaitReturns = sem_timedwait(
                pSemOnWaitingEnding,
                &endTime);
        //LOG("sem_timedwait");
        //int timedwaitReturns = 1;
        return timedwaitReturns == 0;
        //return errno == ETIMEDOUT;
    }
}
