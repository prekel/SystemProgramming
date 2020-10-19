#include <stdio.h>
#include <stdbool.h>

#include <emscripten.h>
#include <SDL2/SDL.h>

#include "Table.h"
#include "Logger.h"

#include "MainWindow.h"

int main(int argc, char** args)
{
    int philosophersCount = 5;
    int minDurationEat = 1000;
    int maxDurationEat = 5000;
    bool isInfinityDuration = false;
    int minSendIntervalDuration = 500;
    int maxSendIntervalDuration = 1500;
    bool isAutoSpawnDisabled =
            minSendIntervalDuration == 0 && maxSendIntervalDuration == 0;

    Table* pTable = CreateTable(philosophersCount, minDurationEat,
                                maxDurationEat,
                                isInfinityDuration);
    InitLogger(pTable, true, stdout, NULL, NULL, NULL);

    MainWindow* pMainWindow = CreateMainWindow(
            512,
            512,
            pTable,
            minSendIntervalDuration,
            maxSendIntervalDuration,
            isAutoSpawnDisabled,
            false,
            true);

    InitVideoMainWindow(pMainWindow);

    StartThreadsMainWindow(pMainWindow);

    emscripten_set_main_loop_arg((em_arg_callback_func) RenderFrame,
                                 pMainWindow->pRendererThreadOptions,
                                 0, 1);

    DestroyMainWindow(pMainWindow);
    DestroyTable(pTable);

    return 0;
}
