#ifndef LOG_H
#define LOG_H

#include <time.h>
#include <string.h>

#include "Fork.h"
#include "Table.h"
#include "Philosopher.h"

#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__

#define PPCAT_NX(A, B) A ## B
#define PPCAT(A, B) PPCAT_NX(A, B)
#define STRINGIZE_NX(A) #A
#define STRINGIZE(A) STRINGIZE_NX(A)

#define LOG_FILE_ALIGN 30
#define LOG_FMT             "[%*s:%d] "
#define LOG_ARGS     (LOG_FILE_ALIGN - sizeof(STRINGIZE(__LINE__))),_FILE, __LINE__

#define LOG_HELPER(format, ...)      Log2(LOG_FMT format, __VA_ARGS__)
#define LOG(message, args...)     LOG_HELPER(message, LOG_ARGS, ## args)
//
//char ForkToChar(Fork* fork);
//
//char PhToChar(Philosopher* fork);
//
//char* TableInfo(Table* pTable);
//
//void LogTableInfo(Table* pTable);
//
void InitLogger(Table* pTable);
//
//void LogPrefix(char* fileName);

void Log(char* fileName, char* format, ...);

void Log2(char* format, ...);

#endif // LOG_H
