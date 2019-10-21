#include <malloc.h>
#include <assert.h>

#include "ArchipelagoCollection.h"

ArchipelagoCollection* ArchipelagoCollectionCreate()
{
    ArchipelagoCollection* pCollection =
            (ArchipelagoCollection*)malloc(sizeof(ArchipelagoCollection));
    assert(pCollection);

    pCollection->pList = LinkedListCreate();
    assert(pCollection->pList);

    return pCollection;
}

void ArchipelagoCollectionAdd(ArchipelagoCollection* pCollection,
                              Archipelago* pArchipelago)
{

}