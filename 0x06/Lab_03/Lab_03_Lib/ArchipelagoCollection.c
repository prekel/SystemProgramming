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
    LinkedListNode* pIterator = ArchipelagoCollectionGetIterator(pCollection);

    do
    {
        Archipelago* pArchipelago =
                ArchipelagoCollectionGetByIterator(pIterator);
        if (strcmp(pArchipelago->Name, name) == 0)
        {
            return pArchipelago;
        }
    } while (ArchipelagoCollectionIteratorNext(&pIterator));

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
