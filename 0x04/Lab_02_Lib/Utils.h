#ifndef UTILS_H
#define UTILS_H

#include <time.h>

/*!
 *
 * \param min
 * \param max
 * \return
 */
int RandomInterval(int min, int max);

struct timespec RandomTime(int minSeconds, int maxSeconds);

double TimespecToDouble(struct timespec* tw);

struct timespec TimespecFromDouble(double seconds);

#endif // UTILS_H
