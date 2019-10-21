#ifndef ACTIONS_H
#define ACTIONS_H

#include "ArchipelagoCollection.h"

typedef enum
{
    ADD, MODIFY, DELETE, PRINT, PRINT_ALL, HAS_ONLY_UNINHABITED, PRINT_WHERE_ISLANDS_COUNT_IS, EXIT
} Action;

int ActionsHandler(ArchipelagoCollection* pCollection, Action action);

void Add(ArchipelagoCollection* pCollection);

void Modify(ArchipelagoCollection* pCollection);

void Delete(ArchipelagoCollection* pCollection);

void Print(ArchipelagoCollection* pCollection);

void PrintAll(ArchipelagoCollection* pCollection);

void HasOnlyUninhabited(ArchipelagoCollection* pCollection);

void PrintWhereIslandsCountIs(ArchipelagoCollection* pCollection);

#endif //ACTIONS_H
