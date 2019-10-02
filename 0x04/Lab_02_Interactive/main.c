#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <signal.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <SDL.h>

#include "Input.h"
#include "Table.h"
#include "Utils.h"
#include "RealTimeTableStateThread.h"
#include "AutoEatThread.h"
#include "Log.h"
#include "PhilosopherEatingThread.h"
#include "EatingInterrupter.h"

#include "RendererThread.h"

#define FILE_NAME "Main_Interactive"

const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;

SDL_Window* g_pWindow = NULL;
SDL_Renderer* g_pRenderer = NULL;

int Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Can't init: %s\n", SDL_GetError());
        return 1;
    }

    g_pWindow = SDL_CreateWindow("Обедающие философы",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SCREEN_WIDTH,
                                 SCREEN_HEIGHT,
                                 SDL_WINDOW_SHOWN);

    if (g_pWindow == NULL)
    {
        fprintf(stderr, "Can't create window: %s\n", SDL_GetError());
        return 1;
    }

    g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (g_pRenderer == NULL)
    {
        fprintf(stderr, "Can't create renderer: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

int Quit()
{
    SDL_DestroyWindow(g_pWindow);

    SDL_DestroyRenderer(g_pRenderer);

    SDL_Quit();

    return 0;
}

//void SigUsr1Handler()
//{
//    LogPrefix(FILE_NAME);
//    printf("Отправка/получение/обработка сигнала SIGUSR1\n");
//}

int main(int argc, char** args)
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif //_WIN32

    if (Init() == 1)
    {
        return 1;
    }

    Table* pTable = CreateTable(0, 9, true);

    InitLogger(pTable);

    StartAllThreads(pTable);


    AutoEatThreadOptions* pAutoEatThreadOptions = CreateAutoEatThreadOptions(
            pTable, 10000, 10000);
    pthread_t autoEatThreadId;
    pthread_create(&autoEatThreadId, NULL, AutoEatThread,
                   pAutoEatThreadOptions);


    struct timespec tw = {0, 200000000};
    RealTimeTableStateThreadOptions* pRealTimeTableStateOptions =
            CreateRealTimeTableStateThreadOptions(pTable, tw);
    pthread_t realTimeTableStateThreadId;
    pthread_create(
            &realTimeTableStateThreadId,
            NULL,
            RealTimeTableStateThread,
            pRealTimeTableStateOptions);

    //DoEatAll(pTable);


    int countedFrames = 0;
    bool run = true;
    SDL_Event e;

    struct timespec tw1 = RandomTime(7, 7);
    int k1 = 0;

    pTable->IsEatingStarted = true;


    RendererThreadOptions* pRendererThreadOptions =
            CreateRendererThreadOptions(pTable, g_pRenderer, SCREEN_WIDTH,
                                        SCREEN_HEIGHT);
    pthread_t rendererThreadId;
    pthread_create(&rendererThreadId, NULL, RendererThread, pRendererThreadOptions);



    //while (run)
    //{

    while (SDL_WaitEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            return 2;
        }

        if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                break;
            }
            if (e.key.keysym.mod & KMOD_ALT)
            {
                char button = e.key.keysym.sym;
                if ('1' <= button && button <='9')
                {
                    int philosopherId = (int)(button - '0');
                    if (philosopherId <= PHILOSOPHERS_COUNT)
                    {
                        InterruptEating(
                                pTable->ppPhilosophers[philosopherId - 1],
                                pTable->pMutex);
                    }
                }


//                if (e.key.keysym.sym == SDLK_1)
//                {
//                    //i/f (pTable->ppPhilosophers[0]->IsEating)
//                    //{
//                    //    LogPrefix(FILE_NAME);
//                    //    printf("Приём пищи философа с номером 1 прерван "
//                    //           "вручную\n");
//                        InterruptEating(pTable->ppPhilosophers[0],
//                                pTable->pMutex);
//                        //pthread_kill(pTable->ppPhilosophers[0]->pThread,
//                        //             SIGUSR1);
//                    //}
////                    else if (pTable->ppPhilosophers[0]->IsWaitingLeftFork)
////                    {
////                        pthread_cond_signal(
////                                pTable->ppPhilosophers[0]->pLeftFork->CondSignalOnRelease);
////                    }
////                    else if (pTable->ppPhilosophers[0]->IsWaitingRightFork)
////                    {
////                        pthread_cond_signal(
////                                pTable->ppPhilosophers[0]->pRightFork->CondSignalOnRelease);
////                    }
//                }
//                if (e.key.keysym.sym == SDLK_2)
//                {
//                    //if (pTable->ppPhilosophers[1]->IsEating)
//                    //{
//                        //LogPrefix(FILE_NAME);
//                        //printf("Приём пищи философа с номером 2 прерван "
//                        //       "вручную\n");
//                        InterruptEating(pTable->ppPhilosophers[1],
//                                        pTable->pMutex);
//                        //pthread_kill(pTable->ppPhilosophers[1]->pThread,
//                        //             SIGUSR1);
//                    //}
//                }
//                if (e.key.keysym.sym == SDLK_3)
//                {
//                    //if (pTable->ppPhilosophers[2]->IsEating)
//                    //{
//                    //    LogPrefix(FILE_NAME);
//                   //     printf("Приём пищи философа с номером 3 прерван "
//                    //           "вручную\n");
//                        InterruptEating(pTable->ppPhilosophers[2],
//                                        pTable->pMutex);
//                        //pthread_kill(pTable->ppPhilosophers[2]->pThread,
//                        //             SIGUSR1);
//                    //}
//                }
//                if (e.key.keysym.sym == SDLK_4)
//                {
//                    //if (pTable->ppPhilosophers[3]->IsEating)
//                    //{
//                    //    LogPrefix(FILE_NAME);
//                     //   printf("Приём пищи философа с номером 4 прерван "
//                     //          "вручную\n");
//                        InterruptEating(pTable->ppPhilosophers[3],
//                                        pTable->pMutex);
//                        //pthread_kill(pTable->ppPhilosophers[3]->pThread,
//                         //            SIGUSR1);
//                    //}
//                }
//                if (e.key.keysym.sym == SDLK_5)
//                {
//                    //if (pTable->ppPhilosophers[4]->IsEating)
//                    //{
//                    //    LogPrefix(FILE_NAME);
//                    //    printf("Приём пищи философа с номером 5 прерван "
//                     //          "вручную\n");
//                        InterruptEating(pTable->ppPhilosophers[4],
//                                        pTable->pMutex);
//                    //    pthread_kill(pTable->ppPhilosophers[4]->pThread,
//                    //                 SIGUSR1);
//                    //}
//                }
            }
            else
            {
                char button = e.key.keysym.sym;
                if ('1' <= button && button <='9')
                {
                    int philosopherId = (int)(button - '0');
                    if (philosopherId <= PHILOSOPHERS_COUNT)
                    {
                        LogPrefix(FILE_NAME);
                        printf("Философ с номером %d вручную отправлен есть"
                               "\n",
                               pTable->ppPhilosophers[philosopherId -1]->PhilosopherId);
                        Eat1(pTable,
                             pTable->ppPhilosophers[philosopherId - 1], tw1,
                             k1++);
                    }
                }

//                if (e.key.keysym.sym == SDLK_1)
//                {
//                    LogPrefix(FILE_NAME);
//                    printf("Философ с номером 1 отправлен есть вручную\n");
//                    Eat1(pTable, pTable->ppPhilosophers[0], tw1, k1++);
//                }
//                if (e.key.keysym.sym == SDLK_2)
//                {
//                    LogPrefix(FILE_NAME);
//                    printf("Философ с номером 2 отправлен есть вручную\n");
//                    Eat1(pTable, pTable->ppPhilosophers[1], tw1, k1++);
//                }
//                if (e.key.keysym.sym == SDLK_3)
//                {
//                    LogPrefix(FILE_NAME);
//                    printf("Философ с номером 3 отправлен есть вручную\n");
//                    Eat1(pTable, pTable->ppPhilosophers[2], tw1, k1++);
//                }
//                if (e.key.keysym.sym == SDLK_4)
//                {
//                    LogPrefix(FILE_NAME);
//                    printf("Философ с номером 4 отправлен есть вручную\n");
//                    Eat1(pTable, pTable->ppPhilosophers[3], tw1, k1++);
//                }
//                if (e.key.keysym.sym == SDLK_5)
//                {
//                    LogPrefix(FILE_NAME);
//                    printf("Философ с номером 5 отправлен есть вручную\n");
//                    Eat1(pTable, pTable->ppPhilosophers[4], tw1, k1++);
//                }
            }
        }
    }

    //pAutoEatThreadOptions->IsMustStop = true;
    LogPrefix(FILE_NAME);
    printf("Завершение программы, ожидание завершения потоков\n");

    //LogTableInfo(pTable);
    //printf("[pid: 0x%08lx] Завершение программы, ожидание завершения потоков...\n",
    //       pthread_self());

    pTable->IsEatingMustEnd = true;

    LogPrefix(FILE_NAME);
    printf("Принудительная отмена потока-спавнера\n");
    pthread_cancel(autoEatThreadId);
    DestroyAutoEatThreadOptions(pAutoEatThreadOptions);

    for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    {
        pthread_mutex_lock(pTable->pMutex);
        if (pTable->ppPhilosophers[i]->IsThreadRunning)
        {
            LogPrefix(FILE_NAME);
            printf("Ожидание завершения потока философа %d\n", pTable->ppPhilosophers[i]->PhilosopherId);

            //LogTableInfo(pTable);
            //printf("[pid: 0x%08lx] Ожидание завершения потока философа %d\n",
            //       pthread_self(), pTable->ppPhilosophers[i]->PhilosopherId);
            sem_post(pTable->ppPhilosophers[i]->pSemOnGoingToEat);
            pthread_mutex_unlock(pTable->pMutex);
            void* pReturned;
            pthread_join(pTable->ppPhilosophers[i]->pThread, &pReturned);
            PhilosopherEatingThreadOptions* pReturnedOptions =
                    (PhilosopherEatingThreadOptions*)pReturned;
            DestroyPhilosopherEatingThreadOptions(pReturnedOptions);
            continue;
        }
        pthread_mutex_unlock(pTable->pMutex);
    }

    pTable->IsEatingEnded = true;

    LogPrefix(FILE_NAME);
    printf("Ожидание завершения потока-наблюдателя\n");
    pthread_join(realTimeTableStateThreadId, NULL);
    DestroyRealTimeTableStateThreadOptions(pRealTimeTableStateOptions);

    LogPrefix(FILE_NAME);
    printf("Ожидание завершения отрисовщика\n");
    pthread_join(rendererThreadId, NULL);
    DestroyRendererThreadOptions(pRendererThreadOptions);

    LogPrefix(FILE_NAME);
    printf("Завершение программы\n");

    DestroyTable(pTable);

    return Quit();
}
