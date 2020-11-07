/// \file
/// \brief Реализация функций из RendererThread.h
/// \details Реализация функций из RendererThread.h.

#include <malloc.h>
#include <math.h>

#ifdef __EMSCRIPTEN__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Logger.h"

#include "RendererThread.h"

/// Чёрный цвет (полная прозрачность)
#define ZERO_RGBA 0
/// Белый цвет (полная непрозрачность)
#define FULL_RGBA 255
/// Красная, зелёная, синяя составляющая цвета философа без потока
#define THREAD_NOT_RUNNING_RGB 64
/// Красная составляющая цвета философа который ест
#define EATING_R 255
/// Зелёная и синяя составляющая цвета философа который ест
#define EATING_GB 64
/// Красная составляющая цвета философа который ожидает
#define WAITING_R 32
/// Зелёная составляющая цвета философа который ожидает
#define WAITING_G 255
/// Синяя составляющая цвета философа который ожидает
#define WAITING_B 64
/// Красная, зелёная, синяя составляющая цвета философа который свободен
#define FREE_RGB 255
/// Красная составляющая цвета занятой вилки
#define USED_R 255
/// Зелёня составляющая цвета занятой вилки
#define USED_G 128
/// Синяя составляющая цвета занятой вилки
#define USED_B 64
/// Красная, зелёная, синяя составляющая цвета свободной вилки
#define NOT_USED_RGB 200

#ifdef ANDROID
/// Числитель масштаба
#define SCALE_NOM 2000
/// Знаменатель масштаба
#define SCALE_DENOM 1000
#else
/// Числитель масштаба
#define SCALE_NOM 1000
/// Знаменатель масштаба
#define SCALE_DENOM 1000
#endif
/// Радиус от центра экрана до середины квадрата философа
#define PHILOSOPHER_RADIUS (200 * SCALE_NOM / SCALE_DENOM)
/// Ширина квадрата философа
#define PHILOSOPHER_WIDTH (60 * SCALE_NOM / SCALE_DENOM)
/// Радиус от центра экрана до середины квадрата вилки
#define FORK_RADIUS (160 * SCALE_NOM / SCALE_DENOM)
/// Ширина квадрата вилки
#define FORK_WIDTH (30 * SCALE_NOM / SCALE_DENOM)

/// Угол на полный оборот
#define FULL_ANGLE 360.0
/// Развёрнутый угол
#define WIDE_ANGLE 180.0
/// Прямой угол
#define RIGHT_ANGLE 90.0

/// Число миллисекунд на 1 кадр, если в 1 секунде 60 кадров
#define VSYNCMS 16

RendererThreadOptions* CreateRendererThreadOptions(
        Table* pTable, SDL_Renderer* pRenderer,
        int screenWidth, int screenHeight)
{
    RendererThreadOptions* pOptions =
            (RendererThreadOptions*) malloc(sizeof(RendererThreadOptions));
    FAILURE_IF_NULLPTR(pOptions);

    pOptions->pTable = pTable;
    pOptions->pRenderer = pRenderer;
    pOptions->ScreenWidth = screenWidth;
    pOptions->ScreenHeight = screenHeight;

    pOptions->pMutex = pTable->pMutex;

    return pOptions;
}

void DestroyRendererThreadOptions(RendererThreadOptions* pOptions)
{
    free(pOptions);
}

/// Вычисляет X-координату сдвинутого на заданный радиус и угол центра экрана.
///
/// \param screenWidth Ширина окна.
/// \param angle Угол.
/// \param r Радиус.
/// \return Вычисляемая координата.
static inline int CenterCircleX(int screenWidth, double angle, double r)
{
    return screenWidth / 2 + (int) (cos(angle * M_PI / WIDE_ANGLE) * r);
}

/// Вычисляет Y-координату сдвинутого на заданный радиус и угол центра экрана.
///
/// \param screenHeight Высота окна.
/// \param angle Угол.
/// \param r Радиус.
/// \return Вычисляемая координата.
static inline int CenterCircleY(int screenHeight, double angle, double r)
{
    return screenHeight / 2 + (int) (sin(angle * M_PI / WIDE_ANGLE) * r);
}

void DrawSquare(
        SDL_Renderer* pRenderer, int screenWidth, int screenHeight,
        int width, int r, double angle)
{
    SDL_Rect rect = {
            CenterCircleX(screenWidth, angle, r) - width / 2,
            CenterCircleY(screenHeight, angle, r) - width / 2,
            width,
            width};
    SDL_RenderFillRect(pRenderer, &rect);
}

void* RenderFrame(RendererThreadOptions* pOptions)
{
    SDL_SetRenderDrawColor(pOptions->pRenderer,
                           ZERO_RGBA, ZERO_RGBA, ZERO_RGBA, ZERO_RGBA);
    SDL_RenderClear(pOptions->pRenderer);
    SDL_SetRenderDrawColor(pOptions->pRenderer,
                           FULL_RGBA, FULL_RGBA, FULL_RGBA, FULL_RGBA);


    for (int i = 0; i < pOptions->pTable->PhilosophersCount; i++)
    {
        if (!pOptions->pTable->ppPhilosophers[i]->IsThreadRunning)
        {
            SDL_SetRenderDrawColor(pOptions->pRenderer,
                                   THREAD_NOT_RUNNING_RGB,
                                   THREAD_NOT_RUNNING_RGB,
                                   THREAD_NOT_RUNNING_RGB,
                                   FULL_RGBA);
        }
        else if (pOptions->pTable->ppPhilosophers[i]->IsEating)
        {
            SDL_SetRenderDrawColor(pOptions->pRenderer,
                                   EATING_R, EATING_GB, EATING_GB,
                                   FULL_RGBA);
        }
        else if (pOptions->pTable->ppPhilosophers[i]->IsWaiting)
        {
            SDL_SetRenderDrawColor(pOptions->pRenderer,
                                   WAITING_R, WAITING_G, WAITING_B,
                                   FULL_RGBA);
        }
        else if (!pOptions->pTable->ppPhilosophers[i]->IsEating)
        {
            SDL_SetRenderDrawColor(pOptions->pRenderer,
                                   FREE_RGB, FREE_RGB, FREE_RGB,
                                   FULL_RGBA);
        }

        double angle =
                FULL_ANGLE / pOptions->pTable->PhilosophersCount * i -
                RIGHT_ANGLE;

        DrawSquare(pOptions->pRenderer,
                   pOptions->ScreenWidth,
                   pOptions->ScreenHeight,
                   PHILOSOPHER_WIDTH,
                   PHILOSOPHER_RADIUS,
                   angle);
    }


    for (int i = 0; i < pOptions->pTable->PhilosophersCount; i++)
    {
        if (pOptions->pTable->ppForks[i]->IsInUse)
        {
            SDL_SetRenderDrawColor(pOptions->pRenderer,
                                   USED_R, USED_G, USED_B, FULL_RGBA);
        }
        else
        {
            SDL_SetRenderDrawColor(pOptions->pRenderer,
                                   NOT_USED_RGB, NOT_USED_RGB,
                                   NOT_USED_RGB, FULL_RGBA);
        }

        double angle =
                FULL_ANGLE / pOptions->pTable->PhilosophersCount * i -
                (RIGHT_ANGLE - (FULL_ANGLE /
                                (pOptions->pTable->PhilosophersCount *
                                 2)));

        DrawSquare(pOptions->pRenderer,
                   pOptions->ScreenWidth,
                   pOptions->ScreenHeight,
                   FORK_WIDTH,
                   FORK_RADIUS,
                   angle);
    }

    SDL_RenderPresent(pOptions->pRenderer);

    return NULL;
}

void* RendererThread(void* pRendererThreadOptions)
{
    LOG("Запуск потока");

    RendererThreadOptions* pOptions = (RendererThreadOptions*)
            pRendererThreadOptions;

    unsigned int ticks1 = SDL_GetTicks();

    while (true)
    {
        if (pOptions->pTable->IsEatingEnded) break;

        RenderFrame(pOptions);

        unsigned int frameMs = SDL_GetTicks() - ticks1;
        ticks1 = SDL_GetTicks();
        if (frameMs < VSYNCMS)
        {
            SDL_Delay(VSYNCMS - frameMs);
        }
    }

    LOG("Завершение потока");

    return NULL;
}