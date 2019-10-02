#ifndef EATINGINTERRUPTER_H
#define EATINGINTERRUPTER_H

#include <pthread.h>
#include <signal.h>

#include "Philosopher.h"

int InterruptEating(Philosopher* pPhilosopher, pthread_mutex_t* pMutex);

#endif //EATINGINTERRUPTER_H
