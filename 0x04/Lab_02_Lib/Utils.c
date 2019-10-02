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

struct timespec RandomTime(int minSeconds, int maxSeconds)
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
