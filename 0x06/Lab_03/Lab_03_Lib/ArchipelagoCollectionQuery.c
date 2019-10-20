#include "ArchipelagoCollectionQuery.h"

bool ArchipelagoCollectionQueryHas1(
        ArchipelagoCollection* pCollection,
        bool (pPredicate)(Archipelago* pArchipelago))
{
    LinkedListNode* pIterator = ArchipelagoCollectionGetIterator(pCollection);
    bool result = false;

    Archipelago* pArchipelago = ArchipelagoCollectionIteratorNext(&pIterator);
    while (pArchipelago)
    {
        if (pPredicate(pArchipelago))
        {
            result = true;
            break;
        }
        pArchipelago = ArchipelagoCollectionIteratorNext(&pIterator);
    }
    return result;
}

ArchipelagoCollection* ArchipelagoCollectionQuerySelectWhereIsN(
        ArchipelagoCollection* pCollection,
        int n,
        bool (pPredicate)(Archipelago* pArchipelago, int n))
{
    LinkedListNode* pIterator = ArchipelagoCollectionGetIterator(pCollection);
    ArchipelagoCollection* pResultCollection = ArchipelagoCollectionCreate();

    Archipelago* pArchipelago = ArchipelagoCollectionIteratorNext(&pIterator);
    while (pArchipelago)
    {
        if (pPredicate(pArchipelago, n))
        {
            ArchipelagoCollectionAdd(pResultCollection, pArchipelago);
        }
        pArchipelago = ArchipelagoCollectionIteratorNext(&pIterator);
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
    return ArchipelagoCollectionQueryHas1(
            pCollection,
            PredicateArchipelagoHasOnlyUninhabited);
}

static bool PredicateArchipelagoIslandsCountIsN(
        Archipelago* pArchipelago,
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