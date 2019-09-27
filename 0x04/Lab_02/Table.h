#ifndef TABLE_H
#define TABLE_H

#include <stdbool.h>

#include "Philosopher.h"
#include "Fork.h"

typedef struct
{
    Philosopher** Philosophers;
    Fork** Forks;
    bool IsEatingStarted;
    bool IsEatingEnded;
} Table;

Table* CreateTable();

void DoEatAll1(Table* pTable);

void DestroyTable(Table* pTable);

#endif // TABLE_H
