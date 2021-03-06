﻿/// \file
/// \brief Реализация функций из MainWindow.h
/// \details Реализация функций из MainWindow.h.

#include <malloc.h>
//#include <sysexits.h>

#include "Logger.h"

#include "MainWindow.h"
#include "ProgramQuitThread.h"

MainWindow*
CreateMainWindow(int screenWidth, int screenHeight, Table* pTable,
                 int minSendIntervalDuration,
                 int maxSendIntervalDuration, bool isAutoSpawnDisabled,
                 bool isRendererAsync,
                 bool isMainCycleAsync)
{
    MainWindow* pMainWindow = (MainWindow*) malloc(sizeof(MainWindow));
    FAILURE_IF_NULLPTR(pMainWindow);

    pMainWindow->ScreenWidth = screenWidth;
    pMainWindow->ScreenHeight = screenHeight;

    pMainWindow->pTable = pTable;

    pMainWindow->MinSendIntervalDuration = minSendIntervalDuration;
    pMainWindow->MaxSendIntervalDuration = maxSendIntervalDuration;

    pMainWindow->IsAutoSpawnDisabled = isAutoSpawnDisabled;

    pMainWindow->MainThreadId = pthread_self();


    pMainWindow->pRendererThreadOptions =
            CreateRendererThreadOptions(pMainWindow->pTable,
                                        pMainWindow->pRenderer,
                                        pMainWindow->ScreenWidth,
                                        pMainWindow->ScreenHeight);
    pMainWindow->IsRendererAsync = isRendererAsync;

    pMainWindow->pMainCycleThreadOptions =
            CreateMainCycleThreadOptions(pMainWindow);
    pMainWindow->IsMainCycleAsync = isMainCycleAsync;

    pMainWindow->pPhilosophersSpawnerThreadOptions =
            CreatePhilosophersSpawnerThreadOptions(
                    pMainWindow->pTable,
                    pMainWindow->MinSendIntervalDuration,
                    pMainWindow->MaxSendIntervalDuration);

    return pMainWindow;
}

int InitVideoMainWindow(MainWindow* pMainWindow)
{
    LOG("Инициализация SDL");
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Не удаётся проинициализировать: %s\n",
                SDL_GetError());
        return 1;
    }

    SDL_version compiledVersion;
    SDL_version linkedVersion;
    SDL_VERSION(&compiledVersion);
    SDL_GetVersion(&linkedVersion);
    LOG("Скомпилированная версия SDL %d.%d.%d",
        compiledVersion.major,
        compiledVersion.minor,
        compiledVersion.patch);
    LOG("Скомпонованная версия SDL %d.%d.%d",
        linkedVersion.major,
        linkedVersion.minor,
        linkedVersion.patch);

    LOG("Создание окна");
    pMainWindow->pWindow = SDL_CreateWindow("Обедающие философы",
                                            SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            pMainWindow->ScreenWidth,
                                            pMainWindow->ScreenHeight,
                                            SDL_WINDOW_SHOWN);

    if (pMainWindow->pWindow == NULL)
    {
        fprintf(stderr, "Не удаётся создать окно: %s\n",
                SDL_GetError());
        return 1;
    }

    LOG("Создание отрисовщика");
    pMainWindow->pRenderer = SDL_CreateRenderer(
            pMainWindow->pWindow,
            -1,
            SDL_RENDERER_SOFTWARE);
    if (pMainWindow->pRenderer == NULL)
    {
        fprintf(stderr, "Не удаётся создать отрисовщик: %s\n",
                SDL_GetError());
        return 1;
    }
    pMainWindow->pRendererThreadOptions->pRenderer = pMainWindow->pRenderer;

    return 0;
}

void StartThreadsMainWindow(MainWindow* pMainWindow)
{
    if (pMainWindow->IsRendererAsync)
    {
        LOG("Запуск потока отрисовщика");
        pthread_create(&pMainWindow->RendererThreadId,
                       NULL,
                       RendererThread,
                       pMainWindow->pRendererThreadOptions);
    }

    if (pMainWindow->IsMainCycleAsync)
    {
        LOG("Запуск потока обработчика событий");
        pthread_create(&pMainWindow->MainCycleThreadId,
                       NULL,
                       MainCycleThread,
                       pMainWindow->pMainCycleThreadOptions);
    }

    LOG("Запуск потоков-философов");
    StartAllThreads(pMainWindow->pTable);

    if (!pMainWindow->IsAutoSpawnDisabled)
    {
        LOG("Запуск потока, отправляющий философов есть");
        pthread_create(&pMainWindow->PhilosophersSpawnerThreadId,
                       NULL,
                       PhilosophersSpawnerThread,
                       pMainWindow->pPhilosophersSpawnerThreadOptions);
    }

    pMainWindow->pTable->IsEatingStarted = true;
}

int RendererMainWindow(MainWindow* pMainWindow)
{
    LOG("Запуск отрисовщика синхронно");
    RendererThread(pMainWindow->pRendererThreadOptions);
    return 0;
}

int MainCycleStep(MainWindow* pMainWindow, SDL_Event event)
{
    if (event.type == SDL_QUIT)
    {
        LOG("Главный цикл завершён событием");

        if (!pMainWindow->pTable->IsEatingEnded)
        {
            // TODO: lock??
            pthread_mutex_lock(pMainWindow->pTable->pMutex);
            LOG("Событие выхода из программы было послано без завершения "
                "потоков и очистки");
            LOG("Завершение программы с кодом 1 (EXIT_FAILURE)");
            return EXIT_FAILURE;
        }

        LOG("Завершение программы с кодом 0 (EXIT_SUCCESS)");

        return EXIT_SUCCESS;
    }

    if (event.type == SDL_KEYDOWN)
    {
        if ((event.key.keysym.sym == SDLK_ESCAPE
             || event.key.keysym.sym == SDLK_AC_BACK)
            && !pMainWindow->pTable->IsEatingMustEnd)
        {
            LOG("Начато завершение программы");

            LOG("Запуск потока, который завершает потоки");

            ProgramQuitThreadOptions* pProgramQuitThreadOptions =
                    CreateProgramQuitThreadOptions(pMainWindow);
            pthread_t programQuitThreadId;
            pthread_create(&programQuitThreadId,
                           NULL,
                           ProgramQuitThread,
                           pProgramQuitThreadOptions);
        }
        if (event.key.keysym.mod & KMOD_CTRL)
        {
            char button = event.key.keysym.sym;
            if ('1' <= button && button <= '9')
            {
                int philosopherId = (int) (button - '0');
                int phIndex = philosopherId - 1;
                if (philosopherId <=
                    pMainWindow->pTable->PhilosophersCount)
                {
                    pthread_mutex_lock(pMainWindow->pTable->pMutex);
                    Philosopher* ph =
                            pMainWindow->pTable->ppPhilosophers[phIndex];
                    if (!ph->IsEating)
                    {
                        LOG("Переключение метки бесконечного времени "
                            "приёма пищи для философа с номером %d",
                            ph->PhilosopherId);
                        ph->IsInfinityDuration = !ph->IsInfinityDuration;
                    }
                    else
                    {
                        LOG("Невозможно переключение метки бесконечного "
                            "времени приёма пищи для философа с "
                            "номером %d",
                            ph->PhilosopherId);
                    }
                    pthread_mutex_unlock(pMainWindow->pTable->pMutex);
                }
            }
        }
        else if (event.key.keysym.mod & KMOD_ALT)
        {
            char button = event.key.keysym.sym;
            if ('1' <= button && button <= '9')
            {
                int philosopherId = (int) (button - '0');
                int phIndex = philosopherId - 1;
                if (philosopherId <=
                    pMainWindow->pTable->PhilosophersCount)
                {
                    Philosopher* ph =
                            pMainWindow->pTable->ppPhilosophers[phIndex];
                    InterruptEating(ph, pMainWindow->pTable->pMutex);
                }
            }
        }
        else if (!pMainWindow->pTable->IsEatingMustEnd)
        {
            char button = event.key.keysym.sym;
            if ('1' <= button && button <= '9')
            {
                int philosopherId = (int) (button - '0');
                int phIndex = philosopherId - 1;
                if (philosopherId <=
                    pMainWindow->pTable->PhilosophersCount)
                {
                    Philosopher* ph =
                            pMainWindow->pTable->ppPhilosophers[phIndex];
                    LOG("Философ с номером %d вручную отправлен есть",
                        ph->PhilosopherId);
                    SpawnPhilosopher(pMainWindow->pTable, ph);
                }
            }
        }
    }

    return -1;
}

int MainCycleMainWindow(MainWindow* pMainWindow)
{
    LOG("Запуск главного цикла");

    SDL_Event event;

    while (SDL_WaitEvent(&event) != 0)
    {
        int ret = MainCycleStep(pMainWindow, event);
        if (ret >= 0)
        {
            return ret;
        }
    }

    LOG("Главный цикл завершён по неизвестной ошибке: %s", SDL_GetError());
    LOG("Завершение программы (главного цикла) с кодом 70 (EX_SOFTWARE)");

    //return EX_SOFTWARE;
    return 70;
}

void StopThreadsMainWindow(MainWindow* pMainWindow)
{
    LOG("Завершение программы, завершение остальных потоков");

    if (pMainWindow->IsRendererAsync)
    {
        LOG("Ожидание завершения отрисовщика");
        pthread_join(pMainWindow->RendererThreadId, NULL);
    }
    if (pMainWindow->IsMainCycleAsync)
    {
        LOG("Ожидание завершения потока обработчика событий");
        pthread_join(pMainWindow->MainCycleThreadId, NULL);
        pMainWindow->MainCycleReturned = pMainWindow->pMainCycleThreadOptions->Returned;
    }
}

int QuitVideoMainWindow(MainWindow* pMainWindow)
{
    LOG("Очистка и завершение отрисовщика, окна и SDL");

    SDL_DestroyRenderer(pMainWindow->pRenderer);

    SDL_DestroyWindow(pMainWindow->pWindow);

    SDL_Quit();

    return 0;
}

void DestroyMainWindow(MainWindow* pMainWindow)
{
    DestroyRendererThreadOptions(pMainWindow->pRendererThreadOptions);
    DestroyMainCycleThreadOptions(pMainWindow->pMainCycleThreadOptions);
    DestroyPhilosophersSpawnerThreadOptions(
            pMainWindow->pPhilosophersSpawnerThreadOptions);
    free(pMainWindow);
}
