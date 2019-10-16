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
static FILE* g_pOutputStream1st;
/// Дополнителый поток для вывода
static FILE* g_pOutputStream2nd;
/// Требуется ли генерировать информацию о столе
static bool g_IsTableInfoRequired;
/// Дополнительный мьютекс (не главный) для логгирования
static pthread_mutex_t g_pLoggerMutex;

/// Дополнительная функция для вывода
static int (* g_pOutputFunction3th)(char*);

/// Ещё дополнительная функция для вывода
static int (* g_pOutputFunction4th)(char*);

/// Кол-во функций для вывода
static const int g_OutputFunctionsCount = 4;

/// Массив функиций для вывода
static int (* g_ppOutputFunctions[g_OutputFunctionsCount])(char*);

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

int WriteStringOutputStream1st(char* format)
{
    int ret = fputs(format, g_pOutputStream1st);
    fflush(g_pOutputStream1st);
    return ret;
}

int WriteStringOutputStream2nd(char* format)
{
    int ret = fputs(format, g_pOutputStream2nd);
    fflush(g_pOutputStream2nd);
    return ret;
}

void InitLogger(Table* pTable,
                bool isTableInfoEnabled,
                FILE* pOutputStream1st,
                FILE* pOutputStream2nd,
                int (* pOutputFunction3th)(char*),
                int (* pOutputFunction4th)(char*))
{
    if (g_IsLoggerInitialized)
    {
        return;
    }

    g_pLoggingTable = pTable;

    g_pOutputStream1st = pOutputStream1st;

    g_pOutputStream2nd = pOutputStream2nd;

    g_pOutputFunction3th = pOutputFunction3th;

    g_pOutputFunction4th = pOutputFunction4th;

    g_IsTableInfoRequired = isTableInfoEnabled;

    g_IsLoggerInitialized = true;

    if (g_pOutputStream1st == NULL
        && g_pOutputStream2nd == NULL
        && g_pOutputFunction3th == NULL
        && g_pOutputFunction4th == NULL)
    {
        g_IsLoggerInitialized = false;
    }

    if (g_pOutputStream1st)
    {
        g_ppOutputFunctions[0] = WriteStringOutputStream1st;
    }
    if (g_pOutputStream2nd)
    {
        g_ppOutputFunctions[1] = WriteStringOutputStream2nd;
    }
    g_ppOutputFunctions[2] = g_pOutputFunction3th;
    g_ppOutputFunctions[3] = g_pOutputFunction4th;

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

    pthread_mutex_lock(&g_pLoggerMutex);

    int len1 = snprintf(NULL, 0, "[%s][tid: 0x%08lx]", result,
                        pthread_self());

    va_list argPtr;
    va_start(argPtr, format);
    int len2 = vsnprintf(NULL, 0, format, argPtr);
    va_end(argPtr);

    char* s = (char*) malloc((len1 + len2 + 1) * sizeof(char));
    FAILURE_IF_NULLPTR(s);
    snprintf(s, len1 + 1, "[%s][tid: 0x%08lx]", result, pthread_self());
    va_start(argPtr, format);
    vsnprintf(s + len1, len2 + 1, format, argPtr);
    va_end(argPtr);

    for (int i = 0; i < g_OutputFunctionsCount; i++)
    {
        if (g_ppOutputFunctions[i])
        {
            g_ppOutputFunctions[i](s);
        }
    }

    free(s);

    pthread_mutex_unlock(&g_pLoggerMutex);
}
