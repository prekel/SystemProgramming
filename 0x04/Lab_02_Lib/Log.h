#ifndef LOG_H
#define LOG_H

#include <time.h>
#include <string.h>

#include "Fork.h"
#include "Table.h"
#include "Philosopher.h"

#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__

#define STRINGIZE_NX(A) #A
#define STRINGIZE(A) STRINGIZE_NX(A)

#define LOG_FILE_ALIGN 30
#define LOG_FMT             "[%*s:%d] "
#define LOG_ARGS     (LOG_FILE_ALIGN - sizeof(STRINGIZE(__LINE__))), _FILE, __LINE__

#define LOG_HELPER(format, ...)      Log(LOG_FMT format, __VA_ARGS__)
#define LOG(message, args...)     LOG_HELPER(message, LOG_ARGS, ## args)

void InitLogger(Table* pTable);

void Log(char* format, ...);

#endif // LOG_H
