#ifndef RENDERERTHREAD_H
#define RENDERERTHREAD_H

#include <SDL.h>

#include "Table.h"

typedef struct {
    Table* pTable;
    SDL_Renderer* pRenderer;
    int ScreenWidth;
    int ScreenHeight;
    pthread_mutex_t* pMutex;
} RendererThreadOptions;

RendererThreadOptions*
CreateRendererThreadOptions(Table* pTable, SDL_Renderer* pRenderer,
                            int screenWidth, int screenHeight);

void DestroyRendererThreadOptions(RendererThreadOptions* pOptions);

void* RendererThread(void* pRendererThreadOptions);

#endif //RENDERERTHREAD_H
