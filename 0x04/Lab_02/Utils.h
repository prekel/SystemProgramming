#ifndef UTILS_H
#define UTILS_H

#include <time.h>

struct timespec RandomTime(int minSeconds, int maxSeconds);

double TimespecToDouble(struct timespec* tw);

char* CurrentTime();

#endif // UTILS_H
