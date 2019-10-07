/// \file
/// \brief Реализация функций из Logger.h
/// \details Реализация функций из Logger.h.

#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>

#include "Logger.h"
#include "Macro.h"

static Table* g_pLoggingTable;

static bool g_IsLoggerInitialized = false;
static FILE* g_pMainOutputStream;
static bool g_IsMainTableInfoEnabled;
static FILE* g_pSecondaryOutputStream;
static bool g_IsSecondaryTableInfoEnabled;
static bool g_IsTableInfoRequired;
static pthread_mutex_t g_pLoggerMutex;

char ForkToChar(Fork* fork)
{
    if (fork->IsInUse)
        return ',';
    else
        return '.';
}

char PhilosopherToChar(Philosopher* philosopher)
{
    if (!philosopher->IsThreadRunning)
        return '-';
    else if (philosopher->IsEating)
        return '=';
    else if (philosopher->IsWaiting)
        return '?';
    else
        return '_';
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

    g_IsTableInfoRequired = isMainTableInfoEnabled || isSecondaryTableInfoEnabled;

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
    if (g_pMainOutputStream) fprintf(g_pMainOutputStream, "[%s][tid: 0x%08lx]", res1, pthread_self());
    if (g_pSecondaryOutputStream) fprintf(g_pSecondaryOutputStream, "[%s][tid: 0x%08lx]", res2, pthread_self());
#endif

    va_list argPtr;
    va_start(argPtr, format);
    if (g_pMainOutputStream) vfprintf(g_pMainOutputStream, format, argPtr);
    if (g_pMainOutputStream) fprintf(g_pMainOutputStream, "\n");
    va_end(argPtr);

    va_start(argPtr, format);
    if (g_pSecondaryOutputStream) vfprintf(g_pSecondaryOutputStream, format, argPtr);
    if (g_pSecondaryOutputStream) fprintf(g_pSecondaryOutputStream, "\n");
    va_end(argPtr);

    fflush(g_pMainOutputStream);

    pthread_mutex_unlock(&g_pLoggerMutex);
}
