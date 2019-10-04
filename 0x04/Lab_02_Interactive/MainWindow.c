#include <malloc.h>

#include "Macro.h"
#include "Log.h"
#include "EatingInterrupter.h"

#include "MainWindow.h"

#include "ProgramQuitThread.h"

#define FILE_NAME "MainWindow"

MainWindow* CreateMainWindow(int screenWidth, int screenHeight, Table* pTable,
                             int minSendIntervalDuration,
                             int maxSendIntervalDuration,
                             bool isAutoSpawnDisabled)
{
    MainWindow* pMainWindow = (MainWindow*) malloc(sizeof(MainWindow));
    FAILURE_IF_NULLPTR(pMainWindow);

    pMainWindow->ScreenWidth = screenWidth;
    pMainWindow->ScreenHeight = screenHeight;

    pMainWindow->pTable = pTable;

    pMainWindow->IsRealTimeTableStateEnabled = false;

    pMainWindow->MinSendIntervalDuration = minSendIntervalDuration;
    pMainWindow->MaxSendIntervalDuration = maxSendIntervalDuration;

    pMainWindow->IsAutoSpawnDisabled = isAutoSpawnDisabled;

    pMainWindow->MainThreadId = pthread_self();

    return pMainWindow;
}

int InitVideoMainWindow(MainWindow* pMainWindow)
{
	Log(FILE_NAME, "Инициализация SDL");
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Не удаётся проинициализировать: %s\n", SDL_GetError
                ());
        return 1;
    }

    SDL_version compiledVersion;
    SDL_version linkedVersion;
    SDL_VERSION(&compiledVersion);
    SDL_GetVersion(&linkedVersion);
	Log(FILE_NAME, "Скомпилированная версия SDL %d.%d.%d",
           compiledVersion.major, compiledVersion.minor, compiledVersion.patch);
    Log(FILE_NAME, "Скомпонованная версия SDL %d.%d.%d",
           linkedVersion.major, linkedVersion.minor, linkedVersion.patch);

    //atexit(SDL_Quit);

    Log(FILE_NAME, "Создание окна");
    pMainWindow->pWindow = SDL_CreateWindow("Обедающие философы",
                                            SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            pMainWindow->ScreenWidth,
                                            pMainWindow->ScreenHeight,
                                            SDL_WINDOW_SHOWN);

    if (pMainWindow->pWindow == NULL)
    {
        fprintf(stderr, "Не удаётся создать окно: %s\n", SDL_GetError());
        return 1;
    }

    Log(FILE_NAME, "Создание отрисовщика");
    pMainWindow->pRenderer = SDL_CreateRenderer(pMainWindow->pWindow, -1,
                                                SDL_RENDERER_ACCELERATED);
    if (pMainWindow->pRenderer == NULL)
    {
        fprintf(stderr, "Не удаётся создать отрисовщик: %s\n", SDL_GetError
                ());
        return 1;
    }

    return 0;
}

void InitAndStartThreadsMainWindow(MainWindow* pMainWindow)
{
    if (pMainWindow->IsRealTimeTableStateEnabled)
    {
        Log(FILE_NAME, "Запуск потока, котрый выводит состояние стола в поток "
               "ошибок");
        pMainWindow->pRealTimeTableStateThreadOptions =
                CreateRealTimeTableStateThreadOptions(pMainWindow->pTable,
                                                      pMainWindow->RealTimeTableStateInterval);
        pthread_create(
                &pMainWindow->RealTimeTableStateThreadId,
                NULL,
                RealTimeTableStateThread,
                pMainWindow->pRealTimeTableStateThreadOptions);
    }

    Log(FILE_NAME, "Запуск потока отрисовщика");
    pMainWindow->pRendererThreadOptions =
            CreateRendererThreadOptions(pMainWindow->pTable,
                                        pMainWindow->pRenderer,
                                        pMainWindow->ScreenWidth,
                                        pMainWindow->ScreenHeight);
    pthread_create(&pMainWindow->RendererThreadId, NULL, RendererThread,
                   pMainWindow->pRendererThreadOptions);

    Log(FILE_NAME, "Запуск потоков-философов");
    StartAllThreads(pMainWindow->pTable);

    if (!pMainWindow->IsAutoSpawnDisabled)
    {
        Log(FILE_NAME, "Запуск потока, отправляющий философов есть");
        pMainWindow->pAutoEatThreadOptions = CreateAutoEatThreadOptions(
                pMainWindow->pTable, pMainWindow->MinSendIntervalDuration,
                pMainWindow->MaxSendIntervalDuration);
        pthread_create(&pMainWindow->AutoEatThreadId, NULL, AutoEatThread,
                       pMainWindow->pAutoEatThreadOptions);
    }

    pMainWindow->pTable->IsEatingStarted = true;
}

int MainCycleMainWindow(MainWindow* pMainWindow)
{
    Log(FILE_NAME, "Запуск главного цикла");

    SDL_Event event;

    while (SDL_WaitEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            Log(FILE_NAME, "Главный цикл завершён принудительно");
            return 2;
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE && !pMainWindow->pTable->IsEatingMustEnd)
            {
                Log(FILE_NAME, "Начато завершение программы");

                if (!pMainWindow->IsAutoSpawnDisabled)
                {
                    Log(FILE_NAME, "Принудительная отмена потока-спавнера");
                    pthread_cancel(pMainWindow->AutoEatThreadId);
                    DestroyAutoEatThreadOptions(
                            pMainWindow->pAutoEatThreadOptions);
                }

                Log(FILE_NAME, "Запуск потока, который завершает потоки");

                pMainWindow->pTable->IsEatingMustEnd = true;

                ProgramQuitThreadOptions* pProgramQuitThreadOptions = CreateProgramQuitThreadOptions(pMainWindow);
                pthread_t programQuitThreadId;
                pthread_create(&programQuitThreadId, NULL, ProgramQuitThread, pProgramQuitThreadOptions);
            }
            if (event.key.keysym.mod & KMOD_CTRL)
            {
                char button = event.key.keysym.sym;
                if ('1' <= button && button <='9')
                {
                    int philosopherId = (int)(button - '0');
                    pthread_mutex_lock(pMainWindow->pTable->pMutex);
                    if (!pMainWindow->pTable->ppPhilosophers[philosopherId - 1]->IsEating)
                    {
                        Log(FILE_NAME, "Переключение метки бесконечного времени приёма пищи для философа с номером %d",
                               pMainWindow->pTable->ppPhilosophers[philosopherId - 1]->PhilosopherId);
                        pMainWindow->pTable->ppPhilosophers[philosopherId - 1]->IsInfinityDuration =
                                !pMainWindow->pTable->ppPhilosophers[philosopherId - 1]->IsInfinityDuration;
                    }
                    else
                    {
                        Log(FILE_NAME, "Неваозможно переключение метки бесконечного времени приёма пищи для философа с номером %d",
                               pMainWindow->pTable->ppPhilosophers[philosopherId - 1]->PhilosopherId);
                    }
                    pthread_mutex_unlock(pMainWindow->pTable->pMutex);
                }
            }
            else if (event.key.keysym.mod & KMOD_ALT)
            {
                char button = event.key.keysym.sym;
                if ('1' <= button && button <='9')
                {
                    int philosopherId = (int)(button - '0');
                    if (philosopherId <= pMainWindow->pTable->PhilosophersCount)
                    {
                        InterruptEating(
                                pMainWindow->pTable->ppPhilosophers[philosopherId - 1],
                                pMainWindow->pTable->pMutex);
                    }
                }
            }
            else if (!pMainWindow->pTable->IsEatingMustEnd)
            {
                char button = event.key.keysym.sym;
                if ('1' <= button && button <='9')
                {
                    int philosopherId = (int)(button - '0');
                    if (philosopherId <= pMainWindow->pTable->PhilosophersCount)
                    {
                        Log(FILE_NAME, "Философ с номером %d вручную отправлен есть",
                               pMainWindow->pTable->ppPhilosophers[philosopherId -1]->PhilosopherId);
                        Eat1(pMainWindow->pTable,
                             pMainWindow->pTable->ppPhilosophers[philosopherId - 1]);
                    }
                }
            }
        }
    }

    Log(FILE_NAME, "Главный цикл завершён по неизвестной ошибке: %s", SDL_GetError());

    return 1;
}

void QuitMainWindow(MainWindow* pMainWindow)
{
    Log(FILE_NAME, "Завершение программы, завершение остальных потоков");

    if (pMainWindow->IsRealTimeTableStateEnabled)
    {
        Log(FILE_NAME, "Ожидание завершения потока-наблюдателя");
        pthread_join(pMainWindow->RealTimeTableStateThreadId, NULL);
        DestroyRealTimeTableStateThreadOptions
        (pMainWindow->pRealTimeTableStateThreadOptions);
    }

    Log(FILE_NAME, "Ожидание завершения отрисовщика");
    pthread_join(pMainWindow->RendererThreadId, NULL);
    DestroyRendererThreadOptions(pMainWindow->pRendererThreadOptions);

    Log(FILE_NAME, "Завершение программы");
}

int QuitVideoMainWindow(MainWindow* pMainWindow)
{
    Log(FILE_NAME, "Очистка и завершение отрисовщика, окна и SDL");

    SDL_DestroyRenderer(pMainWindow->pRenderer);

    SDL_DestroyWindow(pMainWindow->pWindow);

    SDL_Quit();

    return 0;
}

void DestroyMainWindow(MainWindow* pMainWindow)
{
    free(pMainWindow);
}
