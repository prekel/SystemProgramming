#ifndef PROGRAMQUITTHREAD_H
#define PROGRAMQUITTHREAD_H

#include <pthread.h>

typedef struct {
    pthread_t RealTimeTableStateThreadId;
    pthread_t RendererThreadId;
} ProgramQuitThreadOptions;

ProgramQuitThreadOptions* CreateProgramQuitThreadOptions();

void DestroyProgramQuitThreadOptions
        (ProgramQuitThreadOptions* pOptions);

void* ProgramQuitThread(void* pProgramQuitThreadOptions);

#endif //PROGRAMQUITTHREAD_H
