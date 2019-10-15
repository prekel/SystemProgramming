#include <SDL.h>

#include <stdlib.h>
#include <stdbool.h>

#include "Table.h"
#include "Logger.h"
#include "MainWindow.h"

int SDL_main(int argc, char** argv) {

    Table* pTable = CreateTable(9, 1000, 5000, false);

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
