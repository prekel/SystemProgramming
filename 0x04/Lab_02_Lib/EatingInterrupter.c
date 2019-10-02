#include <pthread.h>
#include <signal.h>
#include <stdio.h>

#include "Philosopher.h"
#include "EatingInterrupter.h"
#include "Log.h"

#define FILE_NAME "EatingInterrupter"

struct sigaction g_SignalAction;
bool g_IsEatingInterrupterInit = false;

void SigUsr1Handler()
{
    LogPrefix(FILE_NAME);
    printf("Отправка/получение/обработка сигнала SIGUSR1\n");
}

void InitEatingInterrupter()
{
    LogPrefix(FILE_NAME);
    printf("Инициализация прерывателя приёма пищи\n");

    g_SignalAction.sa_handler = SigUsr1Handler;
    g_SignalAction.sa_flags = SA_RESTART;
    sigemptyset(&g_SignalAction.sa_mask);
    sigaction(SIGUSR1, &g_SignalAction, 0);

    g_IsEatingInterrupterInit = true;
}

int InterruptEating(Philosopher* pPhilosopher, pthread_mutex_t* pMutex)
{
    if (!g_IsEatingInterrupterInit)
    {
        InitEatingInterrupter();
    }
    pthread_mutex_lock(pMutex);
    if (pPhilosopher->IsEating)
    {
        pthread_kill(pPhilosopher->pThread, SIGUSR1);
        pthread_mutex_unlock(pMutex);
        return 0;
    }
    pthread_mutex_unlock(pMutex);
    return 1;
}
