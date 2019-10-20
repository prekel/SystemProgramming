#include <stdio.h>

#include "Actions.h"
#include "ArchipelagoCollection.h"

void Add(ArchipelagoCollection* pCollection)
{
    printf("Введите название архипелага: ");
    printf("Введите кол-во островов архипелага: ");
    printf("Введите кол-во обитаемых островов архипелага: ");
    Archipelago* pArchipelago = ArchipelagoCreate("qwer", 10, 5);
    ArchipelagoCollectionAdd(pCollection, pArchipelago);
}

void Modify(ArchipelagoCollection* pCollection)
{

}

void Delete(ArchipelagoCollection* pCollection)
{

}

void Print(ArchipelagoCollection* pCollection)
{

}

void PrintAll(ArchipelagoCollection* pCollection)
{

}

void HasOnlyUninhabited(ArchipelagoCollection* pCollection)
{

}

void PrintWhereIslandsCountIs(ArchipelagoCollection* pCollection)
{

}
