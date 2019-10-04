#ifndef LOG_H
#define LOG_H

#include <time.h>

#include "Fork.h"
#include "Table.h"
#include "Philosopher.h"

char ForkToChar(Fork* fork);

char PhToChar(Philosopher* fork);

char* TableInfo(Table* pTable);

void LogTableInfo(Table* pTable);

void InitLogger(Table* pTable);

void LogPrefix(char* fileName);

void Log(char* fileName, char* format, ...);

#endif // LOG_H
