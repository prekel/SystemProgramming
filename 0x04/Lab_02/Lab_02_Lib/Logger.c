/// \file
/// \brief Реализация функций из Logger.h
/// \details Реализация функций из Logger.h.

#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>

#include "Logger.h"

/// Логгируемый стол
static Table* g_pLoggingTable;

/// Инициализирон ли логгер
static bool g_IsLoggerInitialized = false;
/// Основной поток для вывода
static FILE* g_pMainOutputStream;
/// Требуется ли выводить информацию о столе в основной поток
static bool g_IsMainTableInfoEnabled;
/// Дополнителый поток для вывода
static FILE* g_pSecondaryOutputStream;
/// Требуется ли выводить информацию о столе в дополнительный поток
static bool g_IsSecondaryTableInfoEnabled;
/// Требуется ли генерировать информацию о столе
static bool g_IsTableInfoRequired;
/// Дополнительный мьютекс (не главный) для логгирования
static pthread_mutex_t g_pLoggerMutex;

/// Преобразует вилку в символ.
///
/// \param pFork Указатель на вилку.
/// \return Занятая вилка - ',', свободная - '.'.
char ForkToChar(Fork* pFork)
{
    if (pFork->IsInUse)
    {
        return ',';
    }
    else
    {
        return '.';
    }
}

/// Преобразует философа в символ.
///
/// \param pPhilosopher Указатель на философа.
/// \return Философ без запущенного потока - '-', обедающий филосов - '=',
/// ожидающий - '?', свободный - '_'.
char PhilosopherToChar(Philosopher* pPhilosopher)
{
    if (!pPhilosopher->IsThreadRunning)
    {
        return '-';
    }
    else if (pPhilosopher->IsEating)
    {
        return '=';
    }
    else if (pPhilosopher->IsWaiting)
    {
        return '?';
    }
    else
    {
        return '_';
    }
}

void InitLogger(Table* pTable, FILE* pMainOutputStream,
                bool isMainTableInfoEnabled, FILE* pSecondaryOutputStream,
                bool isSecondaryTableInfoEnabled)
{
    if (g_IsLoggerInitialized)
    {
        return;
    }

    g_pLoggingTable = pTable;

    g_pMainOutputStream = pMainOutputStream;
    g_IsMainTableInfoEnabled = isMainTableInfoEnabled;

    g_pSecondaryOutputStream = pSecondaryOutputStream;
    g_IsSecondaryTableInfoEnabled = isSecondaryTableInfoEnabled;

    g_IsTableInfoRequired =
            isMainTableInfoEnabled || isSecondaryTableInfoEnabled;

    g_IsLoggerInitialized = true;

    pthread_mutex_init(&g_pLoggerMutex, NULL);
}

void Log(char* format, ...)
{
    if (!g_IsLoggerInitialized)
    {
        return;
    }

    int tableInfoLength = g_IsTableInfoRequired ?
                          g_pLoggingTable->PhilosophersCount * 2 + 1 : 1;
    char result[tableInfoLength];
    if (g_IsTableInfoRequired)
    {
        for (int i = 0; i < g_pLoggingTable->PhilosophersCount; i++)
        {
            result[i * 2] = PhilosopherToChar(
                    g_pLoggingTable->ppPhilosophers[i]);
            result[i * 2 + 1] = ForkToChar(g_pLoggingTable->ppForks[i]);
        }
    }
    result[tableInfoLength - 1] = '\0';

    char empty[] = "";
    char* res1 = g_IsMainTableInfoEnabled ? result : empty;
    char* res2 = g_IsSecondaryTableInfoEnabled ? result : empty;

    pthread_mutex_lock(&g_pLoggerMutex);

#ifdef __MINGW32__
    if (g_pMainOutputStream) fprintf(g_pMainOutputStream, "[%s][tid: 0x%08llx]", res1, pthread_self());
    if (g_pSecondaryOutputStream) fprintf(g_pSecondaryOutputStream, "[%s][tid: 0x%08llx]", res2, pthread_self());
#else
    if (g_pMainOutputStream)
    {
        fprintf(g_pMainOutputStream, "[%s][tid: 0x%08lx]", res1,
                pthread_self());
    }
    if (g_pSecondaryOutputStream)
    {
        fprintf(g_pSecondaryOutputStream, "[%s][tid: 0x%08lx]", res2,
                pthread_self());
    }
#endif

    va_list argPtr;
    va_start(argPtr, format);
    if (g_pMainOutputStream) vfprintf(g_pMainOutputStream, format, argPtr);
    if (g_pMainOutputStream) fprintf(g_pMainOutputStream, "\n");
    va_end(argPtr);

    va_start(argPtr, format);
    if (g_pSecondaryOutputStream)
    {
        vfprintf(g_pSecondaryOutputStream, format, argPtr);
    }
    if (g_pSecondaryOutputStream) fprintf(g_pSecondaryOutputStream, "\n");
    va_end(argPtr);

    fflush(g_pMainOutputStream);

    pthread_mutex_unlock(&g_pLoggerMutex);
}
