#include <malloc.h>

#include "Logger.h"

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

    //pthread_mutex_lock(pOptions->pMutex);
    LOG("Запуск потока");

    pthread_mutex_lock(pOptions->pMainWindow->pTable->pMutex);
    pOptions->pMainWindow->pTable->IsEatingMustEnd = true;

//    if (!pOptions->pMainWindow->IsAutoSpawnDisabled)
//    {
//        LOG("Принудительная остановка потока-спавнера");
//        pthread_cancel(pOptions->pMainWindow->AutoEatThreadId);
//        //pthread_cond_signal(pOptions->pMainWindow->pAutoEatThreadOptions->OnCondQuit);
//        //pthread_join(pOptions->pMainWindow->AutoEatThreadId, NULL);
//        DestroyPhilosophersSpawnerThreadOptions(
//                pOptions->pMainWindow->pAutoEatThreadOptions);
//    }
    pthread_mutex_unlock(pOptions->pMainWindow->pTable->pMutex);

    //pOptions->pMainWindow->pTable->IsEatingMustEnd = true;
    //pthread_mutex_unlock(pOptions->pMutex);

    LOG("Запуск потока, который завершает потоки филосософ");
    PhilosophersWaiterThreadOptions*
            pPhilosophersWaiterThreadOptions =
            CreatePhilosophersWaiterThreadOptions(pOptions->pMainWindow->pTable);
    pthread_t philosophersWaiterThreadId;
    pthread_create(&philosophersWaiterThreadId, NULL,
                   PhilosophersWaiterThread,
                   pPhilosophersWaiterThreadOptions);

    //pthread_mutex_unlock(pOptions->pMutex);

    if (!pOptions->pMainWindow->IsAutoSpawnDisabled)
    {
        LOG("Принудительная остановка потока-cпавнера");
        //pthread_cancel(pOptions->pMainWindow->AutoEatThreadId);
        sem_post(pOptions->pMainWindow->pAutoEatThreadOptions->OnSemQuit);
        //pthread_cond_signal(pOptions->pMainWindow->pAutoEatThreadOptions->OnCondQuit);
    }

    LOG("Ожидание завершения потока, который завершает потоки филосософ");
    pthread_join(philosophersWaiterThreadId, NULL);
    DestroyPhilosophersWaiterThreadOptions(pPhilosophersWaiterThreadOptions);

    if (!pOptions->pMainWindow->IsAutoSpawnDisabled)
    {
        LOG("Ожидание завершения потока-cпавнера");
        pthread_join(pOptions->pMainWindow->AutoEatThreadId, NULL);
        DestroyPhilosophersSpawnerThreadOptions(
                pOptions->pMainWindow->pAutoEatThreadOptions);
    }

    //pthread_mutex_lock(pOptions->pMutex);
    //pOptions->pMainWindow->pTable->IsEatingEnded = true;
    //pthread_mutex_unlock(pOptions->pMutex);
    LOG("Принудительная отмена главного потока");
    SDL_Event event;
    event.type = SDL_QUIT;
    //pthread_mutex_unlock(pOptions->pMutex);
    SDL_PushEvent(&event);

    DestroyProgramQuitThreadOptions(pOptions);
    LOG("Завершение потока");
    //pthread_cancel(pOptions->pMainWindow->MainThreadId);
//    pthread_mutex_unlock(pOptions->pMutex);
//
//    StopThreadsMainWindow(pOptions->pMainWindow);
//
//    QuitVideoMainWindow(pOptions->pMainWindow);
//
//    LOG("Завершение потока и программы");
//
//    DestroyTable(pOptions->pMainWindow->pTable);
//    DestroyMainWindow(pOptions->pMainWindow);
//    DestroyProgramQuitThreadOptions(pOptions);
//
//    fflush(stdout);
//
//    exit(EXIT_SUCCESS);

    return NULL;
}