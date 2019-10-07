/// \file
/// \brief Поток, завершающий программу
/// \details Поток, завершающий программу, его параметры запуска итд.

#ifndef PROGRAMQUITTHREAD_H
#define PROGRAMQUITTHREAD_H

#include <pthread.h>

#include "MainWindow.h"

/// \struct ProgramQuitThreadOptions
///
/// Параметры запуска потока ProgramQuitThread.
typedef struct
{
    /// Указатель на главное окно
    MainWindow* pMainWindow;
    /// Указатель на главный мьютекс
    pthread_mutex_t* pMutex;
} ProgramQuitThreadOptions;

/// Создаёт параметры запуска потока. Требуется очистка с
/// помощью DestroyProgramQuitThreadOptions.
///
/// \param pMainWindow Указатель на главное окно.
/// \return Созданые параметры запуска.
ProgramQuitThreadOptions* CreateProgramQuitThreadOptions(
        MainWindow* pMainWindow);

/// Уничтожает параметры запуска потока.
///
/// \param pOptions
void DestroyProgramQuitThreadOptions(ProgramQuitThreadOptions* pOptions);

/// Функция потока, завершающего программу.
///
/// \param pProgramQuitThreadOptions Указатель на параметры запуска.
/// \return Указатель на параметры, с которыми был запущен.
void* ProgramQuitThread(void* pProgramQuitThreadOptions);

#endif //PROGRAMQUITTHREAD_H
