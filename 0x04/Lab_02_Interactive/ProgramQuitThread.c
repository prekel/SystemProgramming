#include <malloc.h>

#include "Macro.h"
#include "Log.h"

#include "ProgramQuitThread.h"
#include "PhilosophersWaiterThread.h"

#define FILE_NAME "ProgramQuitThread"

ProgramQuitThreadOptions*
CreateProgramQuitThreadOptions(MainWindow* pMainWindow)
{
    ProgramQuitThreadOptions* pOptions = (ProgramQuitThreadOptions*)malloc(sizeof(ProgramQuitThreadOptions));
    FAILURE_IF_NULLPTR(pOptions);

    pOptions->pMainWindow = pMainWindow;

    pOptions->pMutex = pMainWindow->pTable->pMutex;

    return pOptions;
}

void DestroyProgramQuitThreadOptions
        (ProgramQuitThreadOptions* pOptions)
{
    free(pOptions);
}

void* ProgramQuitThread(void* pProgramQuitThreadOptions)
{
    LogPrefix(FILE_NAME);
    printf("Запуск потока\n");

    ProgramQuitThreadOptions* pOptions = (ProgramQuitThreadOptions*)pProgramQuitThreadOptions;

    PhilosophersWaiterThreadOptions*
            pPhilosophersWaiterThreadOptions =
            CreatePhilosophersWaiterThreadOptions(pOptions->pMainWindow->pTable);
    pthread_t philosophersWaiterThreadId;
    pthread_create(&philosophersWaiterThreadId, NULL,
                   PhilosophersWaiterThread,
                   pPhilosophersWaiterThreadOptions);

    pthread_join(philosophersWaiterThreadId, NULL);

    DestroyPhilosophersWaiterThreadOptions(pPhilosophersWaiterThreadOptions);

    LogPrefix(FILE_NAME);
    printf("Принудительная отмена главного потока\n");
    pthread_cancel(pOptions->pMainWindow->MainThreadId);

    QuitMainWindow(pOptions->pMainWindow);

    QuitVideoMainWindow(pOptions->pMainWindow);

    LogPrefix(FILE_NAME);
    DestroyTable(pOptions->pMainWindow->pTable);
    DestroyMainWindow(pOptions->pMainWindow);
    DestroyProgramQuitThreadOptions(pOptions);
    printf("Завершение потока и программы\n");
    fflush(stdout);

    exit(EXIT_SUCCESS);

    return NULL;
}