#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>

#include <SDL.h>
#include <signal.h>

#include "Input.h"

#include "Table.h"
#include "Utils.h"
#include "RealTimeTableStateThread.h"
#include "AutoEatThread.h"
#include "Log.h"

const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;

SDL_Window* win = NULL;
SDL_Surface* john = NULL;
SDL_Renderer* ren = NULL;

int Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Can't init: %s\n", SDL_GetError());
        return 1;
    }

    win = SDL_CreateWindow("Обедающие философы",
                           SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED,
                           SCREEN_WIDTH,
                           SCREEN_HEIGHT,
                           SDL_WINDOW_SHOWN);

    if (win == NULL)
    {
        fprintf(stderr, "Can't create window: %s\n", SDL_GetError());
        return 1;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL)
    {
        fprintf(stderr, "Can't create renderer: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

int Quit()
{
    SDL_FreeSurface(john);

    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}

Table* g_pLoggingTable;

void
DrawRectangle(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(ren, r, g, b, a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(ren, &rect);
}

int CenterCircleX(double angle, double r)
{
    return SCREEN_WIDTH / 2 + (int) (cos(angle * M_PI / 180) * r);
}

int CenterCircleY(double angle, double r)
{
    return SCREEN_HEIGHT / 2 + (int) (sin(angle * M_PI / 180) * r);
}

void* Render(void* pOptions)
{
    //Uint32 ticks0 = SDL_GetTicks();
    Uint32 ticks1 = SDL_GetTicks();
    //int countedFrames = 0;
    bool run = true;
    while (run)
    {
        if (g_pLoggingTable->IsEatingEnded) break;

        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);


        for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
        {
            if (g_pLoggingTable->ppPhilosophers[i]->IsEating)
            {
                SDL_SetRenderDrawColor(ren, 255, 64, 64, 255);
            }
            else if (g_pLoggingTable->ppPhilosophers[i]->IsWaiting)
            {
                SDL_SetRenderDrawColor(ren, 32, 255, 64, 255);
            }
            else if (!g_pLoggingTable->ppPhilosophers[i]->IsEating)
            {
                SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
            }
            SDL_Rect rect = {
                    CenterCircleX(360.0 / PHILOSOPHERS_COUNT * i - 90, 200) -
                    30,
                    CenterCircleY(360.0 / PHILOSOPHERS_COUNT * i - 90, 200) -
                    30, 60, 60};
            SDL_RenderFillRect(ren, &rect);
        }


        for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
        {
            if (g_pLoggingTable->ppForks[i]->IsInUse)
            {
                SDL_SetRenderDrawColor(ren, 255, 128, 64, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
            }
            SDL_Rect rect = {
                    CenterCircleX(360.0 / PHILOSOPHERS_COUNT * i - 54, 160) -
                    15,
                    CenterCircleY(360.0 / PHILOSOPHERS_COUNT * i - 54, 160) -
                    15, 30, 30};
            SDL_RenderFillRect(ren, &rect);
        }

        Uint32 frameMs = SDL_GetTicks() - ticks1;
        //double avgFPS = countedFrames / ((SDL_GetTicks() - ticks0) / 1000.f);
        ticks1 = SDL_GetTicks();


        SDL_RenderPresent(ren);
        //++countedFrames;

        int vsyncms = 17;
        if (frameMs < vsyncms) SDL_Delay(vsyncms - frameMs);
    }

    LogTableInfo(g_pLoggingTable);
    printf("[pid: 0x%08lx][Render] Завершение потока\n", pthread_self());

    return NULL;
}

void your_handler()
{

}

int main(int argc, char** args)
{
    if (Init() == 1)
    {
        return 1;
    }

    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_Rect rect1 = {10, 10, 50, 50};
    SDL_RenderFillRect(ren, &rect1);

//    SDL_Rect rect2 = {70, 10, 50, 50};
//    SDL_RenderDrawRect(ren, &rect2);
//
//    SDL_RenderDrawLine(ren, 10, 70, 640 - 10, 70);

    for (int i = 10; i <= 640 - 10; i += 4)
    {
        SDL_RenderDrawPoint(ren, i, 90);
    }

    SDL_RenderPresent(ren);

    //SDL_Delay(5000);

    Table* pTable = CreateTable();
    g_pLoggingTable = pTable;


    StartAllThreads(pTable);


    AutoEatThreadOptions* pAutoEatThreadOptions = CreateAutoEatThreadOptions(
            pTable);
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


    pthread_t rendererThreadId;
    pthread_create(&rendererThreadId, NULL, Render, NULL);

    struct sigaction sa;
    sa.sa_handler = your_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, 0);


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
                if (e.key.keysym.sym == SDLK_1)
                {
                    if (pTable->ppPhilosophers[0]->IsEating)
                    {
                        pthread_kill(pTable->ppPhilosophers[0]->pThread,
                                     SIGUSR1);
                    }
                    else if (pTable->ppPhilosophers[0]->IsWaitingLeftFork)
                    {
                        pthread_cond_signal(
                                pTable->ppPhilosophers[0]->pLeftFork->CondSignalOnRelease);
                    }
                    else if (pTable->ppPhilosophers[0]->IsWaitingRightFork)
                    {
                        pthread_cond_signal(
                                pTable->ppPhilosophers[0]->pRightFork->CondSignalOnRelease);
                    }
                }
                if (e.key.keysym.sym == SDLK_2)
                {
                    if (pTable->ppPhilosophers[1]->IsEating)
                    {
                        pthread_kill(pTable->ppPhilosophers[1]->pThread,
                                     SIGUSR1);
                    }
                }
                if (e.key.keysym.sym == SDLK_3)
                {
                    if (pTable->ppPhilosophers[2]->IsEating)
                    {
                        pthread_kill(pTable->ppPhilosophers[2]->pThread,
                                     SIGUSR1);
                    }
                }
                if (e.key.keysym.sym == SDLK_4)
                {
                    if (pTable->ppPhilosophers[3]->IsEating)
                    {
                        pthread_kill(pTable->ppPhilosophers[3]->pThread,
                                     SIGUSR1);
                    }
                }
                if (e.key.keysym.sym == SDLK_5)
                {
                    if (pTable->ppPhilosophers[4]->IsEating)
                    {
                        pthread_kill(pTable->ppPhilosophers[4]->pThread,
                                     SIGUSR1);
                    }
                }
            }
            else
            {
                if (e.key.keysym.sym == SDLK_1)
                {
                    Eat1(pTable, pTable->ppPhilosophers[0], tw1, k1++);
                }
                if (e.key.keysym.sym == SDLK_2)
                {
                    Eat1(pTable, pTable->ppPhilosophers[1], tw1, k1++);
                }
                if (e.key.keysym.sym == SDLK_3)
                {
                    Eat1(pTable, pTable->ppPhilosophers[2], tw1, k1++);
                }
                if (e.key.keysym.sym == SDLK_4)
                {
                    Eat1(pTable, pTable->ppPhilosophers[3], tw1, k1++);
                }
                if (e.key.keysym.sym == SDLK_5)
                {
                    Eat1(pTable, pTable->ppPhilosophers[4], tw1, k1++);
                }
            }
        }
    }

    //pAutoEatThreadOptions->IsMustStop = true;
    pTable->IsEatingMustEnd = true;

    LogTableInfo(pTable);
    printf("[pid: 0x%08lx] Завершение программы, ожидание завершения потоков...\n",
           pthread_self());

    for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    {
        pthread_mutex_lock(pTable->pMutex);
        if (pTable->ppPhilosophers[i]->IsThreadRunning)
        {
            LogTableInfo(pTable);
            printf("[pid: 0x%08lx] Ожидание завершения потока философа %d\n",
                   pthread_self(), pTable->ppPhilosophers[i]->PhilosopherId);
            pthread_mutex_unlock(pTable->pMutex);
            pthread_join(pTable->ppPhilosophers[i]->pThread, NULL);
            continue;
        }
        pthread_mutex_unlock(pTable->pMutex);
    }

    pTable->IsEatingEnded = true;

    pthread_join(autoEatThreadId, NULL);
    DestroyAutoEatThreadOptions(pAutoEatThreadOptions);

    pthread_join(realTimeTableStateThreadId, NULL);
    DestroyRealTimeTableStateThreadOptions(pRealTimeTableStateOptions);

    pthread_join(rendererThreadId, NULL);

    DestroyTable(pTable);

    return Quit();
}
