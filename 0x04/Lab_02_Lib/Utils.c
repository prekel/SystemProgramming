#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <errno.h>

#include "Utils.h"

int RandomInterval(int min, int max)
{
    assert(max >= min);
    if (min == max)
        return min;
    return rand() % (max - min) + min;
}

struct timespec RandomTimeS(int minSeconds, int maxSeconds)
{
    assert(maxSeconds >= minSeconds);

    struct timespec tw;
    if (maxSeconds == minSeconds)
    {
        tw.tv_sec = minSeconds;
        tw.tv_nsec = 0;
    }
    else
    {
        tw.tv_sec = RandomInterval(minSeconds, maxSeconds);
        tw.tv_nsec =
                RandomInterval(0, 1000) * 1000000 +
                RandomInterval(0, 1000) * 1000 +
                RandomInterval(0, 1000);
    }
    return tw;
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

double TimespecToDouble(struct timespec duration, bool isInfinityDuration)
{
    if (isInfinityDuration)
    {
        return INFINITY;
    }
    return duration.tv_sec * 1.0 + duration.tv_nsec / 1000000000.0;
}

struct timespec TimespecFromDouble(double seconds)
{
    struct timespec tw = {0,0};

    tw.tv_sec = (int)seconds;
    tw.tv_nsec = (long int)((seconds - (int)seconds) * 1000000000);

    return tw;
}

///
/// \param pSemOnWaitingEnding
/// \param duration
/// \param isInfinityDuration
/// \param pMutex
/// \return Возвращает не ноль, если семафор быстрее таймаута
int SleepOrWaitSem(sem_t* pSemOnWaitingEnding, struct timespec duration,
                   bool isInfinityDuration, pthread_mutex_t* pMutex)
{
    //struct timespec rem = {0, 0};
    if (isInfinityDuration)
    {
        //pthread_mutex_lock(pMutex);
        struct timespec infinityTime = {INT_MAX, NS_IN_S - 1};
        int timedwaitReturns = sem_timedwait(
                pSemOnWaitingEnding,
                &infinityTime);
        //LogPrefix(FILE_NAME);
        //printf("pthread_cond_timedwait вернул %d\n", timedwaitReturns);
        //pthread_mutex_unlock(pMutex);
        return timedwaitReturns == 0;
    }
    else
    {
        //pthread_mutex_lock(pMutex);

        struct timespec currentTime;
        clock_gettime(CLOCK_REALTIME, &currentTime);

        struct timespec endTime = {currentTime.tv_sec + duration.tv_sec, currentTime.tv_nsec + duration.tv_nsec};
        if (endTime.tv_nsec >= NS_IN_S)
        {
            endTime.tv_sec++;
            endTime.tv_nsec -= NS_IN_S;
        }

        int timedwaitReturns = sem_timedwait(
                pSemOnWaitingEnding,
                &endTime);
        //LogPrefix(FILE_NAME);
        //printf("pthread_cond_timedwait вернул %d\n", timedwaitReturns);
        //pthread_mutex_unlock(pMutex);
        return timedwaitReturns == 0;
        //return errno == ETIMEDOUT;
    }
    return 0;
}