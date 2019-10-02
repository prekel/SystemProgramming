#include <pthread.h>
#include <signal.h>
#include <stdio.h>

#include "Philosopher.h"
#include "EatingInterrupter.h"
#include "Log.h"

#define FILE_NAME "EatingInterrupter"

#ifndef _WIN32
struct sigaction g_SignalAction;
#endif //_WIN32
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

#ifdef _WIN32
    LogPrefix(FILE_NAME);
    printf("Прерывание приёма пищи на Windows не реализовано\n");
#elif
    g_SignalAction.sa_handler = SigUsr1Handler;
    g_SignalAction.sa_flags = SA_RESTART;
    sigemptyset(&g_SignalAction.sa_mask);
    sigaction(SIGUSR1, &g_SignalAction, 0);
#endif

    g_IsEatingInterrupterInit = true;
}

int InterruptEating(Philosopher* pPhilosopher, pthread_mutex_t* pMutex)
{
    if (!g_IsEatingInterrupterInit)
    {
        InitEatingInterrupter();
    }
    LogPrefix(FILE_NAME);
    printf("Попытка прервать приём пищи философа с номером %d\n",
            pPhilosopher->PhilosopherId);
#ifdef _WIN32
    LogPrefix(FILE_NAME);
    printf("Прерывание приёма пищи на Windows не реализовано\n");
    return 2;
#elif
    pthread_mutex_lock(pMutex);
    if (pPhilosopher->IsEating)
    {
        pthread_kill(pPhilosopher->pThread, SIGUSR1);
        pthread_mutex_unlock(pMutex);
        LogPrefix(FILE_NAME);
        printf("Приём пищи философа с номером %d прерван\n",
               pPhilosopher->PhilosopherId);
        return 0;
    }
    pthread_mutex_unlock(pMutex);
    LogPrefix(FILE_NAME);
    printf("Философ с номером %d не ест\n",
           pPhilosopher->PhilosopherId);
    return 1;
#endif
}
