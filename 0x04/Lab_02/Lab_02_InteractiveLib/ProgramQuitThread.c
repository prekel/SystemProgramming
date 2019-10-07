/// \file
/// \brief Реализация функций из ProgramQuitThread.h
/// \details Реализация функций из ProgramQuitThread.h.

#include <malloc.h>

#include "Logger.h"
#include "PhilosophersWaiterThread.h"

#include "ProgramQuitThread.h"

ProgramQuitThreadOptions* CreateProgramQuitThreadOptions(
        MainWindow* pMainWindow)
{
    ProgramQuitThreadOptions* pOptions =
            (ProgramQuitThreadOptions*)
                    malloc(sizeof(ProgramQuitThreadOptions));
    FAILURE_IF_NULLPTR(pOptions);

    pOptions->pMainWindow = pMainWindow;

    pOptions->pMutex = pMainWindow->pTable->pMutex;

    return pOptions;
}

void DestroyProgramQuitThreadOptions(ProgramQuitThreadOptions* pOptions)
{
    free(pOptions);
}

void* ProgramQuitThread(void* pProgramQuitThreadOptions)
{
    ProgramQuitThreadOptions* pOptions =
            (ProgramQuitThreadOptions*) pProgramQuitThreadOptions;

    LOG("Запуск потока");

    pthread_mutex_lock(pOptions->pMainWindow->pTable->pMutex);
    pOptions->pMainWindow->pTable->IsEatingMustEnd = true;

    pthread_mutex_unlock(pOptions->pMainWindow->pTable->pMutex);

    LOG("Запуск потока, который завершает потоки филосософ");
    PhilosophersWaiterThreadOptions*
            pPhilosophersWaiterThreadOptions =
            CreatePhilosophersWaiterThreadOptions(
                    pOptions->pMainWindow->pTable);
    pthread_t philosophersWaiterThreadId;
    pthread_create(&philosophersWaiterThreadId, NULL,
                   PhilosophersWaiterThread,
                   pPhilosophersWaiterThreadOptions);

    if (!pOptions->pMainWindow->IsAutoSpawnDisabled)
    {
        LOG("Принудительная остановка потока-cпавнера");
        sem_post(pOptions->pMainWindow->pPhilosophersSpawnerThreadOptions->OnSemQuit);
    }

    LOG("Ожидание завершения потока, который завершает потоки филосософ");
    pthread_join(philosophersWaiterThreadId, NULL);
    DestroyPhilosophersWaiterThreadOptions(pPhilosophersWaiterThreadOptions);

    if (!pOptions->pMainWindow->IsAutoSpawnDisabled)
    {
        LOG("Ожидание завершения потока-cпавнера");
        pthread_join(pOptions->pMainWindow->PhilosophersSpawnerThreadId, NULL);
        DestroyPhilosophersSpawnerThreadOptions(
                pOptions->pMainWindow->pPhilosophersSpawnerThreadOptions);
    }

    LOG("Отправление события выхода главному циклу");
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);

    DestroyProgramQuitThreadOptions(pOptions);
    LOG("Завершение потока");

    return pOptions;
}