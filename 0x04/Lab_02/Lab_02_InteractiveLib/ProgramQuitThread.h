#ifndef PROGRAMQUITTHREAD_H
#define PROGRAMQUITTHREAD_H

#include <pthread.h>

#include "MainWindow.h"

typedef struct {
    MainWindow* pMainWindow;
    pthread_mutex_t* pMutex;
} ProgramQuitThreadOptions;

ProgramQuitThreadOptions*
CreateProgramQuitThreadOptions(MainWindow* pMainWindow);

void DestroyProgramQuitThreadOptions
        (ProgramQuitThreadOptions* pOptions);

void* ProgramQuitThread(void* pProgramQuitThreadOptions);

#endif //PROGRAMQUITTHREAD_H
