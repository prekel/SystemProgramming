#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdbool.h>

/*!
 *
 * \param min
 * \param max
 * \return
 */
int RandomInterval(int min, int max);

struct timespec RandomTimeFromSec(int minSeconds, int maxSeconds);

double TimespecToDouble(struct timespec duration, bool isInfinityDuration);

struct timespec TimespecFromDouble(double seconds);

#endif // UTILS_H
