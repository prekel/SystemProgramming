#include <pthread.h>
#include <stdio.h>

#include "Philosopher.h"
#include "EatingInterrupter.h"
#include "Log.h"

#define FILE_NAME "EatingInterrupter"

//#ifndef __MINGW32__
//struct sigaction g_SignalAction;
//#endif
bool g_IsEatingInterrupterInit = false;
//
//void SigUsr1Handler()
//{
//    LogPrefix(FILE_NAME);
//    printf("Отправка/получение/обработка сигнала SIGUSR1\n");
//}

void InitEatingInterrupter()
{
    Log(FILE_NAME, "Инициализация прерывателя приёма пищи");

//#ifdef __MINGW32__
//    LogPrefix(FILE_NAME);
//    printf("Прерывание небесконечного приёма пищи на Windows не реализовано\n");
//#else
//    g_SignalAction.sa_handler = SigUsr1Handler;
//    g_SignalAction.sa_flags = SA_RESTART;
//    sigemptyset(&g_SignalAction.sa_mask);
//    sigaction(SIGUSR1, &g_SignalAction, 0);
//#endif

    g_IsEatingInterrupterInit = true;
}

int InterruptEating(Philosopher* pPhilosopher, pthread_mutex_t* pMutex)
{
    if (!g_IsEatingInterrupterInit)
    {
        InitEatingInterrupter();
    }
    Log(FILE_NAME, "Попытка прервать приём пищи философа с номером %d",
           pPhilosopher->PhilosopherId);

    pthread_mutex_lock(pMutex);
    if (pPhilosopher->IsEating)
    {
        Log(FILE_NAME, "Приём пищи философа с номером %d прерван",
               pPhilosopher->PhilosopherId);
        pthread_cond_signal(pPhilosopher->pCondOnWaitingEnding);
        pthread_mutex_unlock(pMutex);
        return 0;
    }
    else if (pPhilosopher->IsWaitingLeftFork)
    {
        Log(FILE_NAME, "Ожидание левой вилки философом с номером %d прервано",
               pPhilosopher->PhilosopherId);
        pthread_cond_signal(pPhilosopher->pLeftFork->CondSignalOnRelease);
        pthread_mutex_unlock(pMutex);
        return 0;
    }
    else if (pPhilosopher->IsWaitingRightFork)
    {
        Log(FILE_NAME, "Ожидание правой вилки философом с номером %d прервано",
               pPhilosopher->PhilosopherId);
        pthread_cond_signal(pPhilosopher->pRightFork->CondSignalOnRelease);
        pthread_mutex_unlock(pMutex);
        return 0;
    }
    Log(FILE_NAME, "Философ с номером %d не ест",
           pPhilosopher->PhilosopherId);
    pthread_mutex_unlock(pMutex);
    return 1;
}
