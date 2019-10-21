#include <malloc.h>
#include <assert.h>
#include <string.h>

#include "ArchipelagoCollection.h"

ArchipelagoCollection* ArchipelagoCollectionCreate()
{
    ArchipelagoCollection* pCollection =
            (ArchipelagoCollection*) malloc(sizeof(ArchipelagoCollection));
    assert(pCollection);

    pCollection->pList = LinkedListCreate();
    assert(pCollection->pList);

    return pCollection;
}

void ArchipelagoCollectionDestroy(ArchipelagoCollection* pCollection)
{
    for (LinkedListNode* pIterator =
            ArchipelagoCollectionGetIterator(pCollection);
         pIterator != NULL;
         ArchipelagoCollectionIteratorNext(&pIterator))
    {
        Archipelago* pArchipelago =
                ArchipelagoCollectionGetByIterator(pIterator);
        ArchipelagoDestroy(pArchipelago);
    }
    LinkedListDestroy(pCollection->pList);
    free(pCollection);
}

void ArchipelagoCollectionAdd(ArchipelagoCollection* pCollection,
                              Archipelago* pArchipelago)
{
    LinkedListAppendElement(pCollection->pList, pArchipelago);
}

void ArchipelagoCollectionRemove(ArchipelagoCollection* pCollection,
                                 Archipelago* pArchipelago)
{
    LinkedListRemoveElement(pCollection->pList, pArchipelago);
}

Archipelago* ArchipelagoCollectionFindByName(
        ArchipelagoCollection* pCollection,
        char* name)
{

    for (LinkedListNode* pIterator =
            ArchipelagoCollectionGetIterator(pCollection);
         pIterator != NULL;
         ArchipelagoCollectionIteratorNext(&pIterator))
    {
        Archipelago* pArchipelago =
                ArchipelagoCollectionGetByIterator(pIterator);
        if (strcmp(pArchipelago->Name, name) == 0)
        {
            return pArchipelago;
        }
    }
    return NULL;
}

Archipelago* ArchipelagoCollectionGetFirst(
        ArchipelagoCollection* pCollection)
{
    return (Archipelago*) LinkedListGetFirstElement(pCollection->pList);
}

LinkedListNode* ArchipelagoCollectionGetIterator(
        ArchipelagoCollection* pCollection)
{
    return LinkedListGetFirstNode(pCollection->pList);
}

Archipelago* ArchipelagoCollectionIteratorNext(
        LinkedListNode** ppArchipelagoIterator)
{
    return ArchipelagoCollectionGetByIterator(
            LinkedListIteratorNext(ppArchipelagoIterator));
}

Archipelago* ArchipelagoCollectionGetByIterator(
        LinkedListNode* pArchipelagoIterator)
{
    return (Archipelago*) pArchipelagoIterator->pElement;
}
