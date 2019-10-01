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

Table* g_pLoggingTable;

void LogPrefix(char* fileName);

#endif // LOG_H
