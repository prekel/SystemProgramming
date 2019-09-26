#ifndef TABLE_H
#define TABLE_H

#include "Philosopher.h"
#include "Fork.h"

typedef struct
{
    Philosopher** Philosophers;
    Fork** Forks;
} Table;

Table* CreateTable();

void DestroyTable(Table* pTable);

#endif // TABLE_H
