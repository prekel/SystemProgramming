#include <malloc.h>

#include "Macro.h"
#include "Log.h"
#include "PhilosophersWaiterThread.h"
#include "EatingInterrupter.h"

#include "MainWindow.h"

#define FILE_NAME "MainWindow"

MainWindow* CreateMainWindow(int screenWidth, int screenHeight, Table* pTable,
                             int minSendIntervalDuration,
                             int maxSendIntervalDuration)
{
    MainWindow* pMainWindow = (MainWindow*) malloc(sizeof(MainWindow*));
    FAILURE_IF_NULLPTR(pMainWindow);

    pMainWindow->ScreenWidth = screenWidth;
    pMainWindow->ScreenHeight = screenHeight;

    pMainWindow->pTable = pTable;

    pMainWindow->IsRealTimeTableStateEnabled = false;

    pMainWindow->MinSendIntervalDuration = minSendIntervalDuration;
    pMainWindow->MaxSendIntervalDuration = maxSendIntervalDuration;

    return pMainWindow;
}

void DestroyMainWindow(MainWindow* pMainWindow)
{
    free(pMainWindow);
}

int InitVideoMainWindow(MainWindow* pMainWindow)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Не удаётся проинициализировать: %s\n", SDL_GetError
                ());
        return 1;
    }

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
    InitLogger(pMainWindow->pTable);

    if (pMainWindow->IsRealTimeTableStateEnabled)
    {
        //struct timespec tw = {0, 200000000};
        pMainWindow->pRealTimeTableStateThreadOptions =
                CreateRealTimeTableStateThreadOptions(pMainWindow->pTable,
                                                      pMainWindow->RealTimeTableStateInterval);
        pthread_create(
                &pMainWindow->RealTimeTableStateThreadId,
                NULL,
                RealTimeTableStateThread,
                pMainWindow->pRealTimeTableStateThreadOptions);
    }

    pMainWindow->pRendererThreadOptions =
            CreateRendererThreadOptions(pMainWindow->pTable,
                                        pMainWindow->pRenderer,
                                        pMainWindow->ScreenWidth,
                                        pMainWindow->ScreenHeight);
    pthread_create(&pMainWindow->RendererThreadId, NULL, RendererThread,
                   pMainWindow->pRendererThreadOptions);

    pMainWindow->pAutoEatThreadOptions = CreateAutoEatThreadOptions(
            pMainWindow->pTable, pMainWindow->MinSendIntervalDuration,
            pMainWindow->MaxSendIntervalDuration);
    pthread_create(&pMainWindow->AutoEatThreadId, NULL, AutoEatThread,
                   pMainWindow->pAutoEatThreadOptions);

    StartAllThreads(pMainWindow->pTable);

    pMainWindow->pTable->IsEatingStarted = true;
}

int MainCycleMainWindow(MainWindow* pMainWindow)
{
    SDL_Event e;

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
                LogPrefix(FILE_NAME);
                printf("Завершение программы\n");

                LogPrefix(FILE_NAME);
                printf("Принудительная отмена потока-спавнера\n");
                pthread_cancel(pMainWindow->AutoEatThreadId);
                DestroyAutoEatThreadOptions(pMainWindow->pAutoEatThreadOptions);

                LogPrefix(FILE_NAME);
                printf("Запуск потока, ожидающий "
                       "завершения потоков философов\n");

                pMainWindow->pTable->IsEatingMustEnd = true;

                PhilosophersWaiterThreadOptions*
                        pPhilosophersWaiterThreadOptions =
                        CreatePhilosophersWaiterThreadOptions(pMainWindow->pTable);
                pthread_t philosophersWaiterThreadId;
                pthread_create(&philosophersWaiterThreadId, NULL,
                               PhilosophersWaiterThread,
                               pPhilosophersWaiterThreadOptions);
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
                                pMainWindow->pTable->ppPhilosophers[philosopherId - 1],
                                pMainWindow->pTable->pMutex);
                    }
                }
            }
            else if (!pMainWindow->pTable->IsEatingMustEnd)
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
                               pMainWindow->pTable->ppPhilosophers[philosopherId -1]->PhilosopherId);
                        Eat1(pMainWindow->pTable,
                             pMainWindow->pTable->ppPhilosophers[philosopherId - 1]);
                    }
                }
            }
        }
    }
}

void QuitMainWindow(MainWindow* pMainWindow)
{
    LogPrefix(FILE_NAME);
    printf("Завершение программы, завершение остальных потоков\n");

    if (pMainWindow->IsRealTimeTableStateEnabled)
    {
        LogPrefix(FILE_NAME);
        printf("Ожидание завершения потока-наблюдателя\n");
        pthread_join(pMainWindow->RealTimeTableStateThreadId, NULL);
        DestroyRealTimeTableStateThreadOptions
        (pMainWindow->pRealTimeTableStateThreadOptions);
    }

    LogPrefix(FILE_NAME);
    printf("Ожидание завершения отрисовщика\n");
    pthread_join(pMainWindow->RendererThreadId, NULL);
    DestroyRendererThreadOptions(pMainWindow->pRendererThreadOptions);

    LogPrefix(FILE_NAME);
    printf("Завершение программы\n");

    DestroyTable(pMainWindow->pTable);
}

int QuitVideoMainWindow(MainWindow* pMainWindow)
{
    SDL_DestroyWindow(pMainWindow->pWindow);

    SDL_DestroyRenderer(pMainWindow->pRenderer);

    SDL_Quit();

    return 0;
}