#ifndef ACTIONS_H
#define ACTIONS_H

#include "ArchipelagoCollection.h"

typedef enum
{
    ADD, MODIFY_NAME, MODIFY_COUNT_ISLANDS, MODIFY_COUNT_INHABITED_ISLANDS, DELETE, PRINT, PRINT_ALL, HAS_ONLY_UNINHABITED, PRINT_WHERE_ISLANDS_COUNT_IS, EXIT
} Action;

int ActionsHandler(ArchipelagoCollection* pCollection, Action action);

void Add(ArchipelagoCollection* pCollection);

void ModifyName(ArchipelagoCollection* pCollection);

void ModifyCountIslands(ArchipelagoCollection* pCollection);

void ModifyCountInhabitedIslands(ArchipelagoCollection* pCollection);

void Delete(ArchipelagoCollection* pCollection);

void Print(ArchipelagoCollection* pCollection);

void PrintAll(ArchipelagoCollection* pCollection);

void HasOnlyUninhabited(ArchipelagoCollection* pCollection);

void PrintWhereIslandsCountIs(ArchipelagoCollection* pCollection);

#endif //ACTIONS_H
