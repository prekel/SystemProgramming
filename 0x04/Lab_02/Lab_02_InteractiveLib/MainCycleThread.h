/// \file
/// \brief Поток цикла обработчика событий
/// \details Поток обработчика событий, его параметры запуска итд.

#ifndef MAINCYCLETHREAD_H
#define MAINCYCLETHREAD_H

#include <pthread.h>

/// \struct MainCycleThreadOptions
///
/// Параметры запуска потока MainCycleThread.
typedef struct
{
    /// Указатель на главное окно
    void* pMainWindow;
    /// Указатель на главный мьютекс
    pthread_mutex_t* pMutex;
    // Значение, возвращённое обработчиком событий
    int Returned;
} MainCycleThreadOptions;

/// Создаёт параметры запуска потока. Требуется очистка с
/// помощью DestroyProgramQuitThreadOptions.
///
/// \param pMainWindow Указатель на главное окно.
/// \return Созданые параметры запуска.
MainCycleThreadOptions* CreateMainCycleThreadOptions(
        void* pMainWindow);

/// Уничтожает параметры запуска потока.
///
/// \param pOptions
void DestroyMainCycleThreadOptions(MainCycleThreadOptions* pOptions);

/// Функция потока, завершающего программу.
///
/// \param pMainCycleThreadOptions Указатель на параметры запуска.
/// \return Указатель на параметры, с которыми был запущен.
void* MainCycleThread(void* pMainCycleThreadOptions);

#endif //MAINCYCLETHREAD_H
