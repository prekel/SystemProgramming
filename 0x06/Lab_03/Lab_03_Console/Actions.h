#ifndef ACTIONS_H
#define ACTIONS_H

#include "ArchipelagoCollection.h"

typedef enum Action
{
    ACTION_ADD = 1,
    ACTION_MODIFY_NAME,
    ACTION_MODIFY_COUNT_ISLANDS,
    ACTION_MODIFY_COUNT_INHABITED_ISLANDS,
    ACTION_DELETE,
    ACTION_PRINT,
    ACTION_PRINT_ALL,
    ACTION_HAS_ONLY_UNINHABITED,
    ACTION_PRINT_WHERE_ISLANDS_COUNT_IS,
    ACTION_EXIT
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
