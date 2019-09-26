#ifndef TABLE_H
#define TABLE_H

#include "Philosopher.h"
#include "Fork.h"

typedef struct
{
    Philosopher Philosophers[5];
    Fork Forks[5];
} Table;

Table* CreateTable();

void DestroyTable(Table* pTable);

#endif // TABLE_H
