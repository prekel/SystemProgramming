#include "ArchipelagoCollectionQuery.h"

bool ArchipelagoCollectionQueryHas(
        ArchipelagoCollection* pCollection,
        bool (pPredicate)(Archipelago*))
{
    bool result = false;

    for (LinkedListNode* pIterator =
            ArchipelagoCollectionGetIterator(pCollection);
         pIterator;
         ArchipelagoCollectionIteratorNext(&pIterator))
    {
        Archipelago* pArchipelago =
                ArchipelagoCollectionGetByIterator(pIterator);
        if (pPredicate(pArchipelago))
        {
            result = true;
            break;
        }
    }
    return result;
}

ArchipelagoCollection* ArchipelagoCollectionQuerySelectWhereIsN(
        ArchipelagoCollection* pCollection,
        int n,
        bool (pPredicate)(Archipelago*, int))
{
    ArchipelagoCollection* pResultCollection = ArchipelagoCollectionCreate();

    for (LinkedListNode* pIterator =
            ArchipelagoCollectionGetIterator(pCollection);
         pIterator;
         ArchipelagoCollectionIteratorNext(&pIterator))
    {
        Archipelago* pArchipelago =
                ArchipelagoCollectionGetByIterator(pIterator);
        if (pPredicate(pArchipelago, n))
        {
            ArchipelagoCollectionAdd(pResultCollection, pArchipelago);
        }
    }
    return pResultCollection;
}

static bool PredicateArchipelagoHasOnlyUninhabited(Archipelago* pArchipelago)
{
    return pArchipelago->CountInhabitedIslands == 0;
}

bool ArchipelagoCollectionQueryHasOnlyUninhabited(
        ArchipelagoCollection* pCollection)
{
    return ArchipelagoCollectionQueryHas(
            pCollection,
            PredicateArchipelagoHasOnlyUninhabited);
}

static bool PredicateArchipelagoIslandsCountIsN(Archipelago* pArchipelago,
                                                int n)
{
    return pArchipelago->CountIslands == n;
}

ArchipelagoCollection* ArchipelagoCollectionQuerySelectWhereIslandsCountIs(
        ArchipelagoCollection* pCollection, int islandsCount)
{
    return ArchipelagoCollectionQuerySelectWhereIsN(
            pCollection,
            islandsCount,
            PredicateArchipelagoIslandsCountIsN);
}
