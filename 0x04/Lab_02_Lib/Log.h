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

void LogPrefix(Table* pTable, pthread_t threadId, char* name);

#endif // LOG_H
