#ifndef ACTIONS_H
#define ACTIONS_H

#include "ArchipelagoCollection.h"

void Add(ArchipelagoCollection* pCollection);

void Modify(ArchipelagoCollection* pCollection);

void Delete(ArchipelagoCollection* pCollection);

void Print(ArchipelagoCollection* pCollection);

void PrintAll(ArchipelagoCollection* pCollection);

void HasOnlyUninhabited(ArchipelagoCollection* pCollection);

void PrintWhereIslandsCountIs(ArchipelagoCollection* pCollection);

#endif //ACTIONS_H
