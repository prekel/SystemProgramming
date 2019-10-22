#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#include "Actions.h"
#include "ArchipelagoCollection.h"
#include "ArchipelagoCollectionQuery.h"
#include "Input.h"

static void Add(ArchipelagoCollection* pCollection)
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

static void ModifyName(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString("Введите название архипелага: ", NULL);
    Archipelago* pArchipelago =
            ArchipelagoCollectionFindByName(pCollection, name);
    free(name);

    if (pArchipelago == NULL)
    {
        printf("Архипелаг с таким названием не существует\n");
        return;
    }

    char* newName = CycleInputString("Введите новое название архипелага: ", NULL);
    ArchipelagoSetName(pArchipelago, newName);
    free(newName);
}

static void ModifyCountIslands(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString("Введите название архипелага: ", NULL);
    Archipelago* pArchipelago =
            ArchipelagoCollectionFindByName(pCollection, name);
    free(name);

    if (pArchipelago == NULL)
    {
        printf("Архипелаг с таким названием не существует\n");
        return;
    }

    int newCountIslands =
            CycleInputInt("Введите новое кол-во островов архипелага: ", 10, NULL);
    pArchipelago->CountIslands = newCountIslands;
}

static void ModifyCountInhabitedIslands(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString("Введите название архипелага: ", NULL);
    Archipelago* pArchipelago =
            ArchipelagoCollectionFindByName(pCollection, name);
    free(name);

    if (pArchipelago == NULL)
    {
        printf("Архипелаг с таким названием не существует\n");
        return;
    }

    int newCountInhabitedIslands =
            CycleInputInt("Введите новое кол-во обитаемых островов архипелага: ", 10, NULL);
    pArchipelago->CountIslands = newCountInhabitedIslands;
}

static void Delete(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString("Введите название архипелага: ", NULL);
    Archipelago* pArchipelago =
            ArchipelagoCollectionFindByName(pCollection, name);
    free(name);

    if (pArchipelago == NULL)
    {
        printf("Архипелаг с таким названием не существует\n");
        return;
    }
    ArchipelagoCollectionRemove(pCollection, pArchipelago);
    ArchipelagoDestroy(pArchipelago);
}

static void Print(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString("Введите название архипелага: ", NULL);
    Archipelago* pArchipelago =
            ArchipelagoCollectionFindByName(pCollection, name);
    free(name);

    if (pArchipelago == NULL)
    {
        printf("Архипелаг с таким названием не существует\n");
        return;
    }
    
    char* archipelagoString = ArchipelagoToString(pArchipelago);
    printf("%s\n", archipelagoString);
    free(archipelagoString);
}

static void PrintAll(ArchipelagoCollection* pCollection)
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

static void HasOnlyUninhabited(ArchipelagoCollection* pCollection)
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

static void PrintWhereIslandsCountIs(ArchipelagoCollection* pCollection)
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

    ArchipelagoCollectionDestroy(pQueryResult);
}

static void Help()
{
    for (Action i = ACTION_EXIT; i < ACTION_DEFAULT; i++)
    {
        printf("Введите %d %s\n", i, ActionInfo(i));
    }
}

int ActionExec(ArchipelagoCollection* pCollection, Action action)
{
    printf("\n");
    switch (action)
    {
        case ACTION_EXIT:
            return 0;
        case ACTION_ADD:
            Add(pCollection);
            break;
        case ACTION_MODIFY_NAME:
            ModifyName(pCollection);
            break;
        case ACTION_MODIFY_COUNT_ISLANDS:
            ModifyCountIslands(pCollection);
            break;
        case ACTION_MODIFY_COUNT_INHABITED_ISLANDS:
            ModifyCountInhabitedIslands(pCollection);
            break;
        case ACTION_DELETE:
            Delete(pCollection);
            break;
        case ACTION_PRINT:
            Print(pCollection);
            break;
        case ACTION_PRINT_ALL:
            PrintAll(pCollection);
            break;
        case ACTION_HAS_ONLY_UNINHABITED:
            HasOnlyUninhabited(pCollection);
            break;
        case ACTION_PRINT_WHERE_ISLANDS_COUNT_IS:
            PrintWhereIslandsCountIs(pCollection);
            break;
        case ACTION_HELP:
            Help();
            break;
        default:
            return -1;
    }
    printf("\n");
    fflush(stdout);
    return 1;
}

char* ActionInfo(Action action)
{
    switch (action)
    {
        case ACTION_EXIT:
            return "чтобы завершить программу";
        case ACTION_ADD:
            return "чтобы добавить архипелаг";
        case ACTION_MODIFY_NAME:
            return "чтобы изменить название архипелага";
        case ACTION_MODIFY_COUNT_ISLANDS:
            return "чтобы изменить кол-во островов";
        case ACTION_MODIFY_COUNT_INHABITED_ISLANDS:
            return "чтобы изменить кол-во обитаемых островов";
        case ACTION_DELETE:
            return "чтобы удалить архипелаг";
        case ACTION_PRINT:
            return "чтобы вывести информацию об архипелаге";
        case ACTION_PRINT_ALL:
            return "чтобы вывести информацию о всех архипелагах";
        case ACTION_HAS_ONLY_UNINHABITED:
            return "чтобы выяснить, есть ли только необитаемые архипелаги";
        case ACTION_PRINT_WHERE_ISLANDS_COUNT_IS:
            return "чтобы вывести архипелаги с заданным кол-вом островов";
        case ACTION_HELP:
            return "чтобы вывести список команд";
        default:
            return NULL;
    }
}
