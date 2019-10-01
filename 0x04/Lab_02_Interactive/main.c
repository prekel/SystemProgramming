#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <SDL.h>

#include "Input.h"
#include "Table.h"
#include "Utils.h"
#include "RealTimeTableState.h"

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

Table* g_pTable;

void DrawRectangle(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(ren, r, g, b, a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(ren, &rect);
}

int CenterCircleX(double angle, double r)
{
    return SCREEN_WIDTH / 2 + (int)(cos(angle * M_PI / 180) * r);
}

int CenterCircleY(double angle, double r)
{
    return SCREEN_HEIGHT / 2 + (int)(sin(angle * M_PI / 180) * r);
}

void* Render(void* pOptions)
{
    Uint32 ticks0 = SDL_GetTicks();
    Uint32 ticks1 = SDL_GetTicks();
    int countedFrames = 0;
    bool run = true;
    while (run)
    {
        if (g_pTable->IsEatingEnded) break;

        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);


        for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
        {
            if (g_pTable->ppPhilosophers[i]->IsEating)
            {
                SDL_SetRenderDrawColor(ren, 255, 64, 64, 255);
            }
            else if (g_pTable->ppPhilosophers[i]->IsWaiting)
            {
                SDL_SetRenderDrawColor(ren, 32, 255, 64, 255);
            }
            else if (!g_pTable->ppPhilosophers[i]->IsEating)
            {
                SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
            }
            SDL_Rect rect = {CenterCircleX(360.0 / PHILOSOPHERS_COUNT * i - 90, 200) - 30, CenterCircleY(360.0 / PHILOSOPHERS_COUNT * i - 90, 200) - 30, 60, 60};
            SDL_RenderFillRect(ren, &rect);
        }


        for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
        {
            if (g_pTable->ppForks[i]->IsInUse)
            {
                SDL_SetRenderDrawColor(ren, 255, 128, 64, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
            }
            SDL_Rect rect = {CenterCircleX(360.0 / PHILOSOPHERS_COUNT * i - 54, 160) - 15, CenterCircleY(360.0 / PHILOSOPHERS_COUNT * i - 54, 160) - 15, 30, 30};
            SDL_RenderFillRect(ren, &rect);
        }

        Uint32 frameMs = SDL_GetTicks() - ticks1;
        double avgFPS = countedFrames / ( (SDL_GetTicks() - ticks0) / 1000.f);
        ticks1 = SDL_GetTicks();


        SDL_RenderPresent(ren);
        ++countedFrames;

        int vsyncms = 17;
        if (frameMs < vsyncms) SDL_Delay(vsyncms - frameMs);
    }
    return NULL;
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
    g_pTable = pTable;

    struct timespec tw = {0, 200000000};
    RealTimeTableStateOptions* pRealTimeTableStateOptions =
            CreateRealTimeTableStateOptions(pTable, tw);
    pthread_t realTimeTableStateThreadId;
    pthread_create(
            &realTimeTableStateThreadId,
            NULL,
            RealTimeTableStateThread,
            pRealTimeTableStateOptions);

    //DoEatAll1(pTable);


    int countedFrames = 0;
    bool run = true;
    SDL_Event e;

    struct timespec tw1 = RandomTime(7, 7);
    int k1 = 0;

    pTable->IsEatingStarted = true;


    pthread_t rendererThreadId;
    pthread_create(&rendererThreadId, NULL, Render, NULL);

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
                if (e.key.keysym.sym == SDLK_1)
                {
                    Eat(pTable, pTable->ppPhilosophers[0], tw1, k1++);
                }
                if (e.key.keysym.sym == SDLK_2)
                {
                    Eat(pTable, pTable->ppPhilosophers[1], tw1, k1++);
                }
                if (e.key.keysym.sym == SDLK_3)
                {
                    Eat(pTable, pTable->ppPhilosophers[2], tw1, k1++);
                }
                if (e.key.keysym.sym == SDLK_4)
                {
                    Eat(pTable, pTable->ppPhilosophers[3], tw1, k1++);
                }
                if (e.key.keysym.sym == SDLK_5)
                {
                    Eat(pTable, pTable->ppPhilosophers[4], tw1, k1++);
                }
            }
        }
    //}

    LogTableInfo(pTable);
    printf("[pid: 0x%08lx] Завершение программы, ожидание завершения птооков...\n",
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

    pthread_join(realTimeTableStateThreadId, NULL);
    DestroyRealTimeTableStateOptions(pRealTimeTableStateOptions);

    pthread_join(rendererThreadId, NULL);

    DestroyTable(pTable);

    return Quit();
}
