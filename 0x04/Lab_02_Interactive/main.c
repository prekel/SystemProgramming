#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>

#include "Input.h"
#include "Table.h"
#include "Utils.h"
#include "RealTimeTableState.h"

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 192;

SDL_Window* win = NULL;
SDL_Surface* john = NULL;

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

    return 0;
}

int Quit()
{
    SDL_FreeSurface(john);

    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}

int main(int argc, char** args)
{
    if (Init() == 1)
    {
        return 1;
    }

    Table* pTable = CreateTable();

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


    bool run = true;
    SDL_Event e;

    struct timespec tw1 = RandomTime(7, 7);
    int k1 = 0;

    pTable->IsEatingStarted = true;

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
    printf("[pid: %lu] Завершение программы, ожидание завершения птооков...\n",
           pthread_self());

    for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
    {
        pthread_mutex_lock(pTable->pMutex);
        if (pTable->ppPhilosophers[i]->IsThreadRunning)
        {
            LogTableInfo(pTable);
            printf("[pid: %lu] Ожидание завершения потока философа %d\n",
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

    DestroyTable(pTable);

    return Quit();
}
