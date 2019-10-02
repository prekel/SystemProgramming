#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SDL.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#include "Table.h"

typedef  struct
{
    int ScreenWidth;
    int ScreenHeight;

    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;

    pthread_t RendererThreadId;

    bool IsRealTimeTableStateEnabled;
    struct timespec RealTimeTableStateInterval;

    Table* pTable;
} MainWindow;

MainWindow* CreateMainWindow(int screenWidth, int screenHeight, Table*
pTable);

int InitVideoMainWindow(MainWindow* pMainWindow);

void StartThreadsMainWindow(MainWindow* pMainWindow);

void MainCycleMainWindow(MainWindow* pMainWindow);

void QuitMainWindow(MainWindow* pMainWindow);

int QuitVideoMainWindow(MainWindow* pMainWindow);

void DestroyMainWindow(MainWindow* pMainWindow);

#endif //MAINWINDOW_H
