#ifndef ARCHIPELAGOCOLLECTIONQUERY_H
#define ARCHIPELAGOCOLLECTIONQUERY_H

#include <stdbool.h>
#include "ArchipelagoCollection.h"

bool ArchipelagoCollectionQueryHas(
        ArchipelagoCollection* pCollection,
        bool (pPredicate)(Archipelago*));

ArchipelagoCollection* ArchipelagoCollectionQuerySelectWhereIsN(
        ArchipelagoCollection* pCollection, int n,
        bool ( pPredicate(Archipelago* pArchipelago, int n)));

bool ArchipelagoCollectionQueryHasOnlyUninhabited(
        ArchipelagoCollection* pCollection);

ArchipelagoCollection* ArchipelagoCollectionQuerySelectWhereIslandsCountIs(
        ArchipelagoCollection* pCollection, int islandsCount);

#endif //ARCHIPELAGOCOLLECTIONQUERY_H
