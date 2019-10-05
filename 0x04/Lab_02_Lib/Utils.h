#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdbool.h>

const int MS_IN_S = 1000;
const int NS_IN_MS = 1000000;
const int NS_IN_S = 1000000000;

/*!
 *
 * \param min
 * \param max
 * \return
 */
int RandomInterval(int min, int max);

struct timespec RandomTimeFromSec(int minSeconds, int maxSeconds);

struct timespec RandomTimeFromMs(int minMs, int maxMs);

double TimespecToDouble(struct timespec duration, bool isInfinityDuration);

struct timespec TimespecFromDouble(double seconds);

#endif // UTILS_H
