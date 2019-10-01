#include <stdlib.h>
#include <time.h>
#include <assert.h>

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
    if (maxSeconds - minSeconds == 1)
    {
        tw.tv_sec = minSeconds;
    }
    else
    {
        tw.tv_sec = RandomInterval(minSeconds, maxSeconds);
    }
    tw.tv_nsec =
            RandomInterval(0, 1000) * 1000000ll +
            RandomInterval(0, 1000) * 1000ll +
            RandomInterval(0, 1000);
    return tw;
}

double TimespecToDouble(struct timespec* tw)
{
    return tw->tv_sec * 1.0 + tw->tv_nsec / 1000000000.0;
}

struct timespec TimespecFromDouble(double seconds)
{
    struct timespec tw = {0,0};

    tw.tv_sec = (int)seconds;
    tw.tv_nsec = (long int)((seconds - (int)seconds) * 1000000000);

    return tw;
}