/// \file
/// \brief Реализация функций из MainCycleThread.h
/// \details Реализация функций из MainCycleThread.h.

#include <malloc.h>

#include "Logger.h"
#include "Utils.h"

#include "MainWindow.h"
#include "MainCycleThread.h"

MainCycleThreadOptions* CreateMainCycleThreadOptions(
        void* pMainWindow)
{
    MainCycleThreadOptions* pOptions =
            (MainCycleThreadOptions*)
                    malloc(sizeof(MainCycleThreadOptions));
    FAILURE_IF_NULLPTR(pOptions);

    pOptions->pMainWindow = pMainWindow;

    pOptions->pMutex = ((MainWindow*)pMainWindow)->pTable->pMutex;

    return pOptions;
}

void DestroyMainCycleThreadOptions(MainCycleThreadOptions* pOptions)
{
    free(pOptions);
}

void* MainCycleThread(void* pMainCycleThreadOptions)
{
    MainCycleThreadOptions* pOptions =
            (MainCycleThreadOptions*) pMainCycleThreadOptions;

    LOG("Запуск потока");

    pOptions->Returned = MainCycleMainWindow(pOptions->pMainWindow);

    LOG("Завершение потока");

    return pOptions;
}
