#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

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
