#ifndef LOG_H
#define LOG_H

#include <time.h>
#include <string.h>

#include "Fork.h"
#include "Table.h"
#include "Philosopher.h"
#include "Macro.h"

#define LOG_FILE_ALIGN 30
#define LOG_FMT "[%*s:%d] "
#define LOG_ARGS (LOG_FILE_ALIGN - sizeof(STRINGIZE(__LINE__))), _FILE, __LINE__
#define LOG_HELPER(format, ...) Log(LOG_FMT format, __VA_ARGS__)

#define LOG(message, args...) LOG_HELPER(message, LOG_ARGS, ## args)

void InitLogger(Table* pTable, FILE* pMainOutputStream,
                bool isMainTableInfoEnabled, FILE* pSecondaryOutputStream,
                bool isSecondaryTableInfoEnabled);

void Log(char* format, ...);

#endif // LOG_H
