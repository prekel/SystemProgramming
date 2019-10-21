#ifndef ARCHIPELAGOCOLLECTION_H
#define ARCHIPELAGOCOLLECTION_H

#include "LinkedList.h"
#include "Archipelago.h"
#include "LinkedListNode.h"

typedef struct
{
    LinkedList* pList;
} ArchipelagoCollection;

ArchipelagoCollection* ArchipelagoCollectionCreate();

void ArchipelagoCollectionDestroy(ArchipelagoCollection* pCollection);

void ArchipelagoCollectionAdd(ArchipelagoCollection* pCollection,
                              Archipelago* pArchipelago);

void ArchipelagoCollectionRemove(ArchipelagoCollection* pCollection,
                                 Archipelago* pArchipelago);

Archipelago* ArchipelagoCollectionFindByName(
        ArchipelagoCollection* pCollection,
        char* name);

Archipelago* ArchipelagoCollectionGetFirst(
        ArchipelagoCollection* pCollection);

LinkedListNode* ArchipelagoCollectionGetIterator(
        ArchipelagoCollection* pCollection);

Archipelago* ArchipelagoCollectionIteratorNext(
        LinkedListNode** ppArchipelagoIterator);

Archipelago* ArchipelagoCollectionGetByIterator(
        LinkedListNode* pArchipelagoIterator);

#endif //ARCHIPELAGOCOLLECTION_H
