#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>

#include "Log.h"
#include "Macro.h"

char ForkToChar(Fork* fork)
{
    if (fork->IsInUse)
        return ',';
    else
        return '.';
}
char PhToChar(Philosopher* fork)
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
        result[i * 2] = PhToChar(pTable->ppPhilosophers[i]);
        result[i * 2 + 1] = ForkToChar(pTable->ppForks[i]);
    }
    result[pTable->PhilosophersCount * 2] = '\0';
    return result;
}

void LogTableInfo(Table* pTable)
{
    char* tableInfo = TableInfo(pTable);
    fprintf(stdout, "[%s]", tableInfo);
    free(tableInfo);
}

#define LOG_OUTPUT_STREAM stdout

static Table* g_pLoggingTable;
static pthread_mutex_t g_pLogMutex;
static bool g_IsLoggerInitialized = false;

void InitLogger(Table* pTable)
{
    g_pLoggingTable = pTable;
    pthread_mutex_init(&g_pLogMutex, NULL);

	g_IsLoggerInitialized = true;
}

void LogPrefix(char* fileName)
{
    char* info = TableInfo(g_pLoggingTable);
#ifdef __MINGW32__
    printf("[%s][tid: 0x%08llx][%24s] ", info, pthread_self(), fileName);
#else
    printf("[%s][tid: 0x%08lx][%24s] ", info, pthread_self(), fileName);
#endif
    free(info);
}

void Log(char* fileName, char* format, ...)
{
	if (!g_IsLoggerInitialized)
	{
		return;
	}
	pthread_mutex_lock(&g_pLogMutex);

	LogPrefix(fileName);

	//char* info = TableInfo(g_pLoggingTable);
	//fprintf(LOG_OUTPUT_STREAM, "[%s][tid: 0x%08lx][%24s] ", info, pthread_self(), fileName);
	//free(info);

    va_list argptr;
    va_start(argptr, format);
	vfprintf(LOG_OUTPUT_STREAM, format, argptr);
	fprintf(LOG_OUTPUT_STREAM, "\n");
    va_end(argptr);

    pthread_mutex_unlock(&g_pLogMutex);
}


void LogPrefix1()
{
    char* info = TableInfo(g_pLoggingTable);
#ifdef __MINGW32__
    printf("[%s][tid: 0x%08llx][%24s] ", info, pthread_self(), fileName);
#else
    printf("[%s][tid: 0x%08lx]", info, pthread_self());
#endif
    free(info);
}

void Log2(char* format, ...)
{
    if (!g_IsLoggerInitialized)
    {
        return;
    }
    pthread_mutex_lock(&g_pLogMutex);

    LogPrefix1();

    va_list argptr;
    va_start(argptr, format);
    vfprintf(LOG_OUTPUT_STREAM, format, argptr);
    fprintf(LOG_OUTPUT_STREAM, "\n");
    va_end(argptr);

    pthread_mutex_unlock(&g_pLogMutex);
}