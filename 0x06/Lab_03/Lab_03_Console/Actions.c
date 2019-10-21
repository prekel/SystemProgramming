#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#include "Actions.h"
#include "ArchipelagoCollection.h"
#include "ArchipelagoCollectionQuery.h"
#include "Input.h"

int ActionsHandler(ArchipelagoCollection* pCollection, Action action)
{
    switch (action)
    {
        case ADD:
            Add(pCollection);
            break;
        case MODIFY_NAME:
            ModifyName(pCollection);
            break;
        case MODIFY_COUNT_ISLANDS:
            ModifyCountIslands(pCollection);
            break;
        case MODIFY_COUNT_INHABITED_ISLANDS:
            ModifyCountInhabitedIslands(pCollection);
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
            return 0;
        default:
            return -1;
    }
    fflush(stdout);
    return 1;
}

void Add(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString("Введите название архипелага: ", NULL);
    int countIslands = CycleInputInt("Введите кол-во островов архипелага: ",
                                     10, NULL);
    int countInhabitedIslands;
    do
    {
        countInhabitedIslands = CycleInputInt(
                "Введите кол-во обитаемых островов архипелага: ", 10, NULL);
    } while (countInhabitedIslands > countIslands);
    Archipelago* pArchipelago = ArchipelagoCreate(name, countIslands,
                                                  countInhabitedIslands);
    ArchipelagoCollectionAdd(pCollection, pArchipelago);
    free(name);
}

void ModifyName(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString("Введите название архипелага: ", NULL);
    Archipelago* pArchipelago =
            ArchipelagoCollectionFindByName(pCollection, name);

    char* newName = CycleInputString("Введите новое название архипелага: ", NULL);
    ArchipelagoSetName(pArchipelago, newName);
}

void ModifyCountIslands(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString("Введите название архипелага: ", NULL);
    Archipelago* pArchipelago =
            ArchipelagoCollectionFindByName(pCollection, name);

    int newCountIslands =
            CycleInputInt("Введите новое кол-во островов архипелага: ", 10, NULL);
    pArchipelago->CountIslands = newCountIslands;
}

void ModifyCountInhabitedIslands(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString("Введите название архипелага: ", NULL);
    Archipelago* pArchipelago =
            ArchipelagoCollectionFindByName(pCollection, name);

    int newCountInhabitedIslands =
            CycleInputInt("Введите новое кол-во обитаемых островов архипелага: ", 10, NULL);
    pArchipelago->CountIslands = newCountInhabitedIslands;
}

void Delete(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString("Введите название архипелага: ", NULL);
    ArchipelagoCollectionRemove(pCollection, ArchipelagoCollectionFindByName(pCollection, name));
}

void Print(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString("Введите название архипелага: ", NULL);
    char* archipelagoString = ArchipelagoToString(ArchipelagoCollectionFindByName(pCollection, name));
    printf("%s\n", archipelagoString);
    free(archipelagoString);
}

void PrintAll(ArchipelagoCollection* pCollection)
{
    for (LinkedListNode* pIterator =
            ArchipelagoCollectionGetIterator(pCollection);
         pIterator != NULL;
         ArchipelagoCollectionIteratorNext(&pIterator))
    {
        Archipelago* pArchipelago =
                ArchipelagoCollectionGetByIterator(pIterator);
        char* archipelagoString = ArchipelagoToString(pArchipelago);
        printf("%s\n", archipelagoString);
        free(archipelagoString);
    }
}

void HasOnlyUninhabited(ArchipelagoCollection* pCollection)
{
    bool hasOnlyUninhabited =
            ArchipelagoCollectionQueryHasOnlyUninhabited(pCollection);

    if (hasOnlyUninhabited)
    {
        printf("Имеются архипелаги, состоящие только из необитаемых островов\n");
    }
    else
    {
        printf("Отсутствуют архипелаги, состоящие только из необитаемых островов\n");
    }
}

void PrintWhereIslandsCountIs(ArchipelagoCollection* pCollection)
{
    int countIslands =
            CycleInputInt("Введите кол-во островов архипелага: ", 10, NULL);

    ArchipelagoCollection* pQueryResult =
            ArchipelagoCollectionQuerySelectWhereIslandsCountIs(pCollection,
                                                                countIslands);

    for (LinkedListNode* pIterator =
            ArchipelagoCollectionGetIterator(pQueryResult);
         pIterator != NULL;
         ArchipelagoCollectionIteratorNext(&pIterator))
    {
        Archipelago* pArchipelago =
                ArchipelagoCollectionGetByIterator(pIterator);
        char* archipelagoString = ArchipelagoToString(pArchipelago);
        printf("%s\n", archipelagoString);
        free(archipelagoString);
    }
}
