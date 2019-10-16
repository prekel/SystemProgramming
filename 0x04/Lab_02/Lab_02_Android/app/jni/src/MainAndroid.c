#include <stdlib.h>
#include <stdbool.h>

#include <SDL.h>

#include <android/log.h>

#include "Table.h"
#include "Logger.h"
#include "MainWindow.h"

int AndroidLog(char* format)
{
    int ret = __android_log_write(ANDROID_LOG_INFO, "Lab_02_Android", format);
    return ret;
}

int SDL_main(int argc, char** argv)
{
    Table* pTable = CreateTable(6, 1000, 5000, false);
    //Table* pTable = CreateTable(6000, 1000, 10000, false);

    //InitLogger(pTable, false, NULL, NULL, AndroidLog, NULL);
    InitLogger(pTable, true, NULL, NULL, AndroidLog, NULL);

    MainWindow* pMainWindow = CreateMainWindow(
            1080,
            2280,
            pTable,
            500,
            //0,
            1500,
            //1,
            false,
            false,
            true);

    InitVideoMainWindow(pMainWindow);

    StartThreadsMainWindow(pMainWindow);

    RendererMainWindow(pMainWindow);

    int mainCycleReturned = pMainWindow->MainCycleReturned;

    DestroyMainWindow(pMainWindow);
    DestroyTable(pTable);

    return mainCycleReturned;
}
