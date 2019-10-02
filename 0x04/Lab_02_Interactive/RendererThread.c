#include <malloc.h>
#include <math.h>

#include <SDL.h>

#include "Log.h"
#include "Macro.h"

#include "RendererThread.h"

#define FILE_NAME "RendererThread"

RendererThreadOptions*
CreateRendererThreadOptions(Table* pTable, SDL_Renderer* pRenderer,
                            int screenWidth, int screenHeight)
{
    RendererThreadOptions* pOptions = (RendererThreadOptions*)malloc(sizeof
            (RendererThreadOptions));
    FAILURE_IF_NULLPTR(pOptions);

    pOptions->pTable = pTable;
    pOptions->pRenderer = pRenderer;
    pOptions->ScreenWidth = screenWidth;
    pOptions->ScreenHeight = screenHeight;

    return pOptions;
}

void DestroyRendererThreadOptions(RendererThreadOptions* pOptions)
{
    free(pOptions);
}

int CenterCircleX(int screenWidth, double angle, double r)
{
    return screenWidth / 2 + (int) (cos(angle * M_PI / 180) * r);
}

int CenterCircleY(int screenHeight, double angle, double r)
{
    return screenHeight / 2 + (int) (sin(angle * M_PI / 180) * r);
}

void* RendererThread(void* pRendererThreadOptions)
{
    LogPrefix(FILE_NAME);
    printf("Запуск потока\n");

    RendererThreadOptions* pOptions = (RendererThreadOptions*)
            pRendererThreadOptions;

    //Uint32 ticks0 = SDL_GetTicks();
    Uint32 ticks1 = SDL_GetTicks();
    //int countedFrames = 0;
    bool run = true;
    while (run)
    {
        if (pOptions->pTable->IsEatingEnded) break;

        SDL_SetRenderDrawColor(pOptions->pRenderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(pOptions->pRenderer);
        SDL_SetRenderDrawColor(pOptions->pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);


        for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
        {
            if (pOptions->pTable->ppPhilosophers[i]->IsEating)
            {
                SDL_SetRenderDrawColor(pOptions->pRenderer, 255, 64, 64, 255);
            }
            else if (pOptions->pTable->ppPhilosophers[i]->IsWaiting)
            {
                SDL_SetRenderDrawColor(pOptions->pRenderer, 32, 255, 64, 255);
            }
            else if (!pOptions->pTable->ppPhilosophers[i]->IsEating)
            {
                SDL_SetRenderDrawColor(pOptions->pRenderer, 255, 255, 255, 255);
            }
            SDL_Rect rect = {
                    CenterCircleX(pOptions->ScreenWidth, 360.0 /
                    PHILOSOPHERS_COUNT * i -
                    90,
                            200) -
                    30,
                    CenterCircleY(pOptions->ScreenHeight, 360.0 / PHILOSOPHERS_COUNT *
                    i - 90, 200) -
                    30, 60, 60};
            SDL_RenderFillRect(pOptions->pRenderer, &rect);
        }


        for (int i = 0; i < PHILOSOPHERS_COUNT; i++)
        {
            if (pOptions->pTable->ppForks[i]->IsInUse)
            {
                SDL_SetRenderDrawColor(pOptions->pRenderer, 255, 128, 64, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(pOptions->pRenderer, 200, 200, 200, 255);
            }
            SDL_Rect rect = {
                    CenterCircleX(pOptions->ScreenWidth, 360.0 /
                    PHILOSOPHERS_COUNT * i - 54, 160) -
                    15,
                    CenterCircleY(pOptions->ScreenHeight, 360.0 / PHILOSOPHERS_COUNT * i - 54, 160) -
                    15, 30, 30};
            SDL_RenderFillRect(pOptions->pRenderer, &rect);
        }

        Uint32 frameMs = SDL_GetTicks() - ticks1;
        //double avgFPS = countedFrames / ((SDL_GetTicks() - ticks0) / 1000.f);
        ticks1 = SDL_GetTicks();


        SDL_RenderPresent(pOptions->pRenderer);
        //++countedFrames;

        int vsyncms = 17;
        if (frameMs < vsyncms) SDL_Delay(vsyncms - frameMs);
    }

    LogPrefix(FILE_NAME);
    printf("Завершение потока\n");

    //LogTableInfo(g_pLoggingTable);
    //printf("[pid: 0x%08lx][Render] Завершение потока\n", pthread_self());

    return NULL;
}