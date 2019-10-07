/// \file
/// \brief Поток отрисовщика
/// \details Поток отрисовщикка, параметры его запуска итд.

#ifndef RENDERERTHREAD_H
#define RENDERERTHREAD_H

#include <SDL.h>

#include "Table.h"

/// \struct
///
/// Параметры запуска RendererThread.
typedef struct
{
    /// Указатель на стол
    Table* pTable;
    /// Указатель на отрисовщик
    SDL_Renderer* pRenderer;
    /// Ширина окна
    int ScreenWidth;
    /// Высота окна
    int ScreenHeight;
    /// Указатель на главный мьютекс
    pthread_mutex_t* pMutex;
} RendererThreadOptions;

/// Создаёт параметры запуска потока. Требуется очистка с
/// помощью DestroyRendererThreadOptions.
///
/// \param pTable Указатель на стол.
/// \param pRenderer Указатель на отрисовщик.
/// \param screenWidth Ширина окна.
/// \param screenHeight Высота окна.
/// \return Указатель на созданные параметры потока.
RendererThreadOptions* CreateRendererThreadOptions(
        Table* pTable, SDL_Renderer* pRenderer,
        int screenWidth, int screenHeight);

/// Уничтожает параметры потока.
///
/// \param pOptions Указатель на парамеры потока.
void DestroyRendererThreadOptions(RendererThreadOptions* pOptions);

/// Функция потока отрисовщика. Цикл, рисующий состояние стола примерно
/// 60 раз в секунду. Тёмно-серый цвет - философ с незапущенным потоком,
/// красный - философ который ест, зелёный - ожидает, белый - свободен;
/// светло-серый - свободная вилка, оранжевый - занятая вилка.
///
/// \param pRendererThreadOptions Указатель на параметры запуска потока.
/// \return Указатель на параметры с которыми был запущен.
void* RendererThread(void* pRendererThreadOptions);

#endif //RENDERERTHREAD_H
