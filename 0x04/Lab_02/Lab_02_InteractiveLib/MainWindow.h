/// \file
/// \brief Главное окно
/// \details Главное окно, функции создания, уничтожения, инициализации,
/// главного цикла итд.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#ifdef __EMSCRIPTEN__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Table.h"
#include "PhilosophersSpawnerThread.h"
#include "MainCycleThread.h"
#include "RendererThread.h"

/// \struct MainWindow
///
/// Главное окно.
typedef struct
{
    /// Ширина окна
    int ScreenWidth;
    /// Высота окна
    int ScreenHeight;

    /// Указатель на окно
    SDL_Window* pWindow;
    /// Указатель на отрисовщик
    SDL_Renderer* pRenderer;

    /// Указатель на параметры запуска потока, отправляющего философов
    PhilosophersSpawnerThreadOptions* pPhilosophersSpawnerThreadOptions;
    /// Идентификатор потока, отправляющий философов
    pthread_t PhilosophersSpawnerThreadId;

    /// Указатель на параметры запуска потока отрисовщика
    RendererThreadOptions* pRendererThreadOptions;
    /// Идентификатор потока отрисовщика
    pthread_t RendererThreadId;
    /// Нужен ли поток отрисовщика, запускаемый в StartThreadsMainWindow
    bool IsRendererAsync;

    /// Указатель на параметры запуска потока обработчика событий
    MainCycleThreadOptions* pMainCycleThreadOptions;
    /// Идентификатор потока обработчика событий
    pthread_t MainCycleThreadId;
    /// Нужен ли поток обработчика событий, запускаемый в StartThreadsMainWindow
    bool IsMainCycleAsync;

    /// Идентификатор главного потока
    pthread_t MainThreadId;

    /// Выключена ли автоматическая отправка философов
    bool IsAutoSpawnDisabled;

    /// Указатель на стол
    Table* pTable;

    /// Нижная граница случайного времени между отправками в миллисекундах
    int MinSendIntervalDuration;
    /// Верхняя граница случайного времени между отправками в миллисекундах
    int MaxSendIntervalDuration;

    int MainCycleReturned;
} MainWindow;

/// Создаёт главное окно. Требуется очистка с помощью DestroyMainWindow.
///
/// \param screenWidth Ширина окна.
/// \param screenHeight Высота окна.
/// \param pTable Указатель на стол.
/// \param minSendIntervalDuration Нижная граница случайного времени между
/// отправками в миллисекундах.
/// \param maxSendIntervalDuration Верхняя граница случайного времени между
/// отправками в миллисекундах.
/// \param isAutoSpawnDisabled Выключена ли автоматическая отправка философов.
/// \return Указатель на созданное главное окно.
MainWindow *
CreateMainWindow(int screenWidth, int screenHeight, Table *pTable, int minSendIntervalDuration,
                 int maxSendIntervalDuration, bool isAutoSpawnDisabled, bool isRendererAsync,
                 bool isMainCycleAsync);

/// Инициализирует SDL, окно, отрисовщик
///
/// \param pMainWindow Указатель на главное окно.
/// \return 0 в случае успеха, 1 если не удалось что-либо проинициализировать
int InitVideoMainWindow(MainWindow* pMainWindow);

/// Запускает потоки: поток отрисовщика и потоки философов
///
/// \param pMainWindow Указатель на главное окно.
void StartThreadsMainWindow(MainWindow* pMainWindow);

/// Синхронный запуск отрисовщика.
///
/// \param pMainWindow Указатель на главное окно.
/// \return 0 в случае успешного завершения
int RendererMainWindow(MainWindow* pMainWindow);

int MainCycleMainWindowPool(MainWindow* pMainWindow);

/// Главный цикл приложения. Обрабатывает события. (Синхронный запуск).
///
/// \param pMainWindow Указатель на главное окно.
/// \return 0 в случае успешного завершения, 1 в случае принудительного,
/// 70 в случае неизвестной ошибки
int MainCycleMainWindow(MainWindow* pMainWindow);

/// Завершает потоки (поток отрисовщика).
///
/// \param pMainWindow Указатель на главное окно.
void StopThreadsMainWindow(MainWindow* pMainWindow);

/// Завершает SDL, уничтожает окно и отрисовщик.
///
/// \param pMainWindow Указатель на главное окно.
/// \return 0
int QuitVideoMainWindow(MainWindow* pMainWindow);

/// Уничтожает главное окно.
///
/// \param pMainWindow Указатель на главное окно.
void DestroyMainWindow(MainWindow* pMainWindow);

#endif //MAINWINDOW_H
