#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#include "Actions.h"
#include "ArchipelagoCollection.h"
#include "Input.h"

int ActionsHandler(ArchipelagoCollection* pCollection, Action action)
{
    switch (action)
    {
        case ADD:
            Add(pCollection);
            break;
        case MODIFY:
            Modify(pCollection);
            break;
        case DELETE:
            Delete(pCollection);
            break;
        case PRINT:
            Print(pCollection);
            break;
        case PRINT_ALL:
            PrintAll(pCollection);
            break;
        case HAS_ONLY_UNINHABITED:
            HasOnlyUninhabited(pCollection);
            break;
        case PRINT_WHERE_ISLANDS_COUNT_IS:
            PrintWhereIslandsCountIs(pCollection);
            break;
        case EXIT:
            return 1;
        default:
            return -1;
    }
    return 0;
}

void Add(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString("Введите название архипелага: ", NULL);
    int countIslands = CycleInputInt("Введите кол-во островов архипелага: ", 10, NULL);
    int countInhabitedIslands;
    do {
        countInhabitedIslands = CycleInputInt("Введите кол-во обитаемых островов архипелага: ", 10, NULL);
    } while (countInhabitedIslands > countIslands);
    Archipelago* pArchipelago = ArchipelagoCreate(name, countIslands, countInhabitedIslands);
    ArchipelagoCollectionAdd(pCollection, pArchipelago);
    free(name);
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
