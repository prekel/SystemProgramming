#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>

#include "Log.h"
#include "Macro.h"

#define LOG_OUTPUT_STREAM stdout

static Table* g_pLoggingTable;
static pthread_mutex_t g_pLogMutex;
static bool g_IsLoggerInitialized = false;

char ForkToChar(Fork* fork)
{
    if (fork->IsInUse)
        return ',';
    else
        return '.';
}
char PhilosopherToChar(Philosopher* fork)
{
    if (fork->IsEating)
        return '=';
    if (fork->IsWaiting)
        return '?';
    else
        return '_';
}

char* TableInfo(Table* pTable)
{
    char* result = (char*)malloc((pTable->PhilosophersCount * 2 + 1) * sizeof(char));
    FAILURE_IF_NULLPTR(result);
    for (int i = 0; i < pTable->PhilosophersCount; i++)
    {
        result[i * 2] = PhilosopherToChar(pTable->ppPhilosophers[i]);
        result[i * 2 + 1] = ForkToChar(pTable->ppForks[i]);
    }
    result[pTable->PhilosophersCount * 2] = '\0';
    return result;
}

void InitLogger(Table* pTable)
{
    g_pLoggingTable = pTable;
    pthread_mutex_init(&g_pLogMutex, NULL);

	g_IsLoggerInitialized = true;
}

void LogPrefix()
{
    char* info = TableInfo(g_pLoggingTable);
#ifdef __MINGW32__
    printf("[%s][tid: 0x%08llx]", info, pthread_self());
#else
    printf("[%s][tid: 0x%08lx]", info, pthread_self());
#endif
    free(info);
}

void Log(char* format, ...)
{
    if (!g_IsLoggerInitialized)
    {
        return;
    }
    //pthread_mutex_lock(&g_pLogMutex);

    LogPrefix();

    va_list argPtr;
    va_start(argPtr, format);
    vfprintf(LOG_OUTPUT_STREAM, format, argPtr);
    fprintf(LOG_OUTPUT_STREAM, "\n");
    va_end(argPtr);

    fflush(LOG_OUTPUT_STREAM);

    //pthread_mutex_unlock(&g_pLogMutex);
}
