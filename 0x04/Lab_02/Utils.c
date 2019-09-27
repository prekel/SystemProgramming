#include <stdlib.h>
#include <time.h>

#include "Utils.h"

int RandomInterval(int min, int max)
{
    return rand() % (max - min) + min;
}

struct timespec RandomTime(int minSeconds, int maxSeconds)
{
    struct timespec tw;
    tw.tv_sec = RandomInterval(minSeconds, maxSeconds) + minSeconds;
    tw.tv_nsec = RandomInterval(0, 1000) * 1000000ll +
            RandomInterval(0, 1000) % 1000 * 1000ll +
            RandomInterval(0, 1000) % 1000;
    return tw;
}

double TimespecToDouble(struct timespec* tw)
{
    return tw->tv_sec * 1.0 + tw->tv_nsec / 1000000000.0;
}
