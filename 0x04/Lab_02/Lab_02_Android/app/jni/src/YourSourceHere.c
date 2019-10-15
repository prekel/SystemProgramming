#include <stdlib.h>
#include <stdbool.h>

#include <SDL.h>

#include <android/log.h>

#include "Table.h"
#include "Logger.h"
#include "MainWindow.h"

int LogFunction1(char* format, ...)
{
    va_list argPtr;
    va_start(argPtr, format);
    int ret = __android_log_vprint(ANDROID_LOG_INFO, "Lab_02_Android", format, argPtr);
    va_end(argPtr);
    return ret;
}

int LogFunction2(char* format, va_list argPtr)
{
    return __android_log_vprint(ANDROID_LOG_INFO, "Lab_02_Android", format, argPtr);
}

int SDL_main(int argc, char** argv) {
    Table* pTable = CreateTable(9, 1000, 5000, false);

    InitLogger(pTable, stdout, true, NULL, false);
    g_pFunction1 = LogFunction1;
    g_pFunction2 = LogFunction2;

    MainWindow* pMainWindow = CreateMainWindow(1080, 2280, pTable, 500, 1500, false, false, true);
    pMainWindow->IsRendererAsync = false;

    InitVideoMainWindow(pMainWindow);

    StartThreadsMainWindow(pMainWindow);

    RendererMainWindow(pMainWindow);

    int mainCycleReturned = pMainWindow->MainCycleReturned;

    DestroyMainWindow(pMainWindow);
    DestroyTable(pTable);

    return mainCycleReturned;
}
