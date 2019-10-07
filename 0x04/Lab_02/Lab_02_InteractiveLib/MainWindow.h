/// \file
/// \brief Главное окно
/// \details Главное окно, функции создания, уничтожения, инициализации, главного цикла итд.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#include <SDL.h>

#include "Table.h"
#include "PhilosophersSpawnerThread.h"

#include "RendererThread.h"

/// \struct MainWindow
///
/// Главное окно.
typedef  struct
{
    int ScreenWidth;
    int ScreenHeight;

    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;

    PhilosophersSpawnerThreadOptions* pAutoEatThreadOptions;
    pthread_t AutoEatThreadId;

    RendererThreadOptions* pRendererThreadOptions;
    pthread_t RendererThreadId;

    pthread_t MainThreadId;

    bool IsAutoSpawnDisabled;

    Table* pTable;

    int MinSendIntervalDuration;
    int MaxSendIntervalDuration;
} MainWindow;

/// Создаёт главное окно. Требуется очистка с помощью DestroyMainWindow.
///
/// \param screenWidth Ширина окна.
/// \param screenHeight Высота окна.
/// \param pTable Стол.
/// \param minSendIntervalDuration Нижняя граница
/// \param maxSendIntervalDuration
/// \param isAutoSpawnDisabled
/// \return
MainWindow* CreateMainWindow(int screenWidth, int screenHeight, Table* pTable,
                             int minSendIntervalDuration,
                             int maxSendIntervalDuration,
                             bool isAutoSpawnDisabled);

int InitVideoMainWindow(MainWindow* pMainWindow);

void InitAndStartThreadsMainWindow(MainWindow* pMainWindow);

int MainCycleMainWindow(MainWindow* pMainWindow);

void QuitMainWindow(MainWindow* pMainWindow);

int QuitVideoMainWindow(MainWindow* pMainWindow);

void DestroyMainWindow(MainWindow* pMainWindow);

#endif //MAINWINDOW_H
