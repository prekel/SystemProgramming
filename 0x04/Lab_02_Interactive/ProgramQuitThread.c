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
    ProgramQuitThreadOptions* pOptions = (ProgramQuitThreadOptions*)pProgramQuitThreadOptions;

    pthread_mutex_lock(pOptions->pMutex);
    Log(FILE_NAME, "Запуск потока");
    pthread_mutex_unlock(pOptions->pMutex);

    PhilosophersWaiterThreadOptions*
            pPhilosophersWaiterThreadOptions =
            CreatePhilosophersWaiterThreadOptions(pOptions->pMainWindow->pTable);
    pthread_t philosophersWaiterThreadId;
    pthread_create(&philosophersWaiterThreadId, NULL,
                   PhilosophersWaiterThread,
                   pPhilosophersWaiterThreadOptions);

    pthread_join(philosophersWaiterThreadId, NULL);

    DestroyPhilosophersWaiterThreadOptions(pPhilosophersWaiterThreadOptions);

    pthread_mutex_lock(pOptions->pMutex);
    Log(FILE_NAME, "Принудительная отмена главного потока");
    pthread_cancel(pOptions->pMainWindow->MainThreadId);
    pthread_mutex_unlock(pOptions->pMutex);

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