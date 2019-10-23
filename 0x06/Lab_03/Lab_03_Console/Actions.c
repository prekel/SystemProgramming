/// \file
/// \brief Реализация функций из Actions.h
/// \details Реализация функций из Actions.h.

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>

#include "Actions.h"
#include "ArchipelagoCollection.h"
#include "ArchipelagoCollectionQuery.h"
#include "Input.h"

#define MAX_INT_LENGTH 11

#define MIN_COUNT_ISLANDS 2

#define MAX_COUNT 999999999

#define ENTER_ARCHIPELAGO_NAME "Введите название архипелага: "

#define ENTER_COUNT_ISLANDS "Введите кол-во островов архипелага (не менее 2): "

#define ENTER_INHABITED_COUNT_ISLANDS "Введите кол-во обитаемых островов архипелага (не более %d): "

#define ARCHIPELAGO_NOT_EXIST "Архипелаг с таким названием не существует\n"

#define ENTER_NEW_ARCHIPELAGO_NAME "Введите новое название архипелага: "

#define ENTER_NEW_COUNT_ISLANDS "Введите новое кол-во островов архипелага (не менее %d): "

#define ENTER_NEW_INHABITED_COUNT_ISLANDS "Введите новое кол-во обитаемых островов архипелага (не более %d): "

#define HAS_ONLY_UNINHABITED_TRUE "Имеются архипелаги, состоящие только из необитаемых островов\n"

#define HAS_ONLY_UNINHABITED_FALSE "Отсутствуют архипелаги, состоящие только из необитаемых островов\n"

#define ALREADY_EXIST "Архипелаг с таким названием уже существует\n"

#define COLLECTION_EMPTY "Архипелаги отсутствуют\n"

#define HELP_ENTER_ACTION "Введите %d %s\n"

#define HELP_COUNT "Числа вводятся от 0 по %d, если не указано иное\n"

#define HELP_STRINGS "Строки вводятся длиной хотя бы в 1 символ\n"

/// Чекер для строк.
///
/// \param name Строка для проверки.
/// \return Истина если длина больше или равна 1.
static bool NameChecker(char* name)
{
    return strlen(name) >= 1;
}

/// Чекер для кол-ва островов.
///
/// \param count Кол-во островов для проверки.
/// \return Истина если от двух по MAX_COUNT.
static bool CountIslandsChecker(int count)
{
    return MIN_COUNT_ISLANDS <= count && count <= MAX_COUNT;
}

/// Чекер для кол-ва обитаемых остров.
///
/// \param count Кол-во обитаемых островов.
/// \return Истина если от 0 по MAX_COUNT.
static bool CountInhabitedIslandsChecker(int count)
{
    return 0 <= count && count <= MAX_COUNT;
}

/// Добавление архипелага.
///
/// \param pCollection Указатель на коллекцию архепилагов.
static void Add(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString(NameChecker, ENTER_ARCHIPELAGO_NAME);

    if (ArchipelagoCollectionFindByName(pCollection, name))
    {
        printf(ALREADY_EXIST);
    }
    else
    {
        int countIslands = CycleInputInt(
                MAX_INT_LENGTH, CountIslandsChecker, ENTER_COUNT_ISLANDS);
        int countInhabitedIslands;
        do
        {
            countInhabitedIslands =
                    CycleInputInt(MAX_INT_LENGTH,
                                  CountInhabitedIslandsChecker,
                                  ENTER_INHABITED_COUNT_ISLANDS,
                                  countIslands);
        } while (countInhabitedIslands > countIslands);
        Archipelago* pArchipelago =
                ArchipelagoCreate(name, countIslands, countInhabitedIslands);

        ArchipelagoCollectionAdd(pCollection, pArchipelago);
    }
    free(name);
}

/// Изменение названия архипелага.
///
/// \param pCollection Указатель на коллекцию архепилагов.
static void ModifyName(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString(NameChecker, ENTER_ARCHIPELAGO_NAME);
    Archipelago* pArchipelago =
            ArchipelagoCollectionFindByName(pCollection, name);

    free(name);
    if (pArchipelago == NULL)
    {
        printf(ARCHIPELAGO_NOT_EXIST);
        return;
    }
    char* newName = CycleInputString(
            NameChecker, ENTER_NEW_ARCHIPELAGO_NAME);
    if (ArchipelagoCollectionFindByName(pCollection, newName))
    {
        printf(ALREADY_EXIST);
    }
    else
    {
        ArchipelagoSetName(pArchipelago, newName);
    }

    free(newName);
}

/// Изменение кол-ва островов архипелага.
///
/// \param pCollection Указатель на коллекцию архепилагов.
static void ModifyCountIslands(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString(NameChecker, ENTER_ARCHIPELAGO_NAME);
    Archipelago* pArchipelago =
            ArchipelagoCollectionFindByName(pCollection, name);
    free(name);

    if (pArchipelago == NULL)
    {
        printf(ARCHIPELAGO_NOT_EXIST);
        return;
    }

    int newCountIslands;
    do
    {
        newCountIslands =
                CycleInputInt(MAX_INT_LENGTH,
                              CountIslandsChecker,
                              ENTER_NEW_COUNT_ISLANDS,
                              pArchipelago->CountInhabitedIslands);
    } while (newCountIslands < pArchipelago->CountInhabitedIslands);
    pArchipelago->CountIslands = newCountIslands;
}

/// Изменение кол-ва обитаемых островов архипелага.
///
/// \param pCollection Указатель на коллекцию архепилагов.
static void ModifyCountInhabitedIslands(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString(NameChecker, ENTER_ARCHIPELAGO_NAME);
    Archipelago* pArchipelago =
            ArchipelagoCollectionFindByName(pCollection, name);
    free(name);

    if (pArchipelago == NULL)
    {
        printf(ARCHIPELAGO_NOT_EXIST);
        return;
    }

    int newCountInhabitedIslands;
    do
    {
        newCountInhabitedIslands =
                CycleInputInt(MAX_INT_LENGTH,
                              CountInhabitedIslandsChecker,
                              ENTER_NEW_INHABITED_COUNT_ISLANDS,
                              pArchipelago->CountIslands);
    } while (newCountInhabitedIslands > pArchipelago->CountIslands);

    pArchipelago->CountInhabitedIslands = newCountInhabitedIslands;
}

/// Удаление архипелага.
///
/// \param pCollection Указатель на коллекцию архепилагов.
static void Delete(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString(NameChecker, ENTER_ARCHIPELAGO_NAME);
    Archipelago* pArchipelago =
            ArchipelagoCollectionFindByName(pCollection, name);
    free(name);

    if (pArchipelago == NULL)
    {
        printf(ARCHIPELAGO_NOT_EXIST);
        return;
    }

    ArchipelagoCollectionRemove(pCollection, pArchipelago);
    ArchipelagoDestroy(pArchipelago);
}

/// Вывод информации об архипелаге.
///
/// \param pCollection Указатель на коллекцию архепилагов.
static void Print(ArchipelagoCollection* pCollection)
{
    char* name = CycleInputString(NameChecker, ENTER_ARCHIPELAGO_NAME);
    Archipelago* pArchipelago =
            ArchipelagoCollectionFindByName(pCollection, name);
    free(name);

    if (pArchipelago == NULL)
    {
        printf(ARCHIPELAGO_NOT_EXIST);
        return;
    }

    char* archipelagoString = ArchipelagoToString(pArchipelago);
    printf("%s\n", archipelagoString);
    free(archipelagoString);
}

/// Вывод информации обо всех архипелагах.
///
/// \param pCollection Указатель на коллекцию архепилагов.
static void PrintAll(ArchipelagoCollection* pCollection)
{
    if (pCollection->pList->Count == 0)
    {
        printf(COLLECTION_EMPTY);
        return;
    }
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

/// Имеются ли архипелаги с только необитаемымы островами.
///
/// \param pCollection Указатель на коллекцию архепилагов.
static void HasOnlyUninhabited(ArchipelagoCollection* pCollection)
{
    bool hasOnlyUninhabited =
            ArchipelagoCollectionQueryHasOnlyUninhabited(pCollection);

    if (hasOnlyUninhabited)
    {
        printf(HAS_ONLY_UNINHABITED_TRUE);
    }
    else
    {
        printf(HAS_ONLY_UNINHABITED_FALSE);
    }
}

/// Вывод архипелагов с заданным числом островов.
///
/// \param pCollection Указатель на коллекцию архепилагов.
static void PrintWhereIslandsCountIs(ArchipelagoCollection* pCollection)
{
    int countIslands =
            CycleInputInt(MAX_INT_LENGTH, CountIslandsChecker,
                          ENTER_COUNT_ISLANDS);

    ArchipelagoCollection* pQueryResult =
            ArchipelagoCollectionQuerySelectWhereIslandsCountIs(pCollection,
                                                                countIslands);

    if (pQueryResult->pList->Count == 0)
    {
        printf(COLLECTION_EMPTY);
    }
    else
    {
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

    ArchipelagoCollectionDestroy(pQueryResult);
}

/// Справка о действии.
///
/// \param action Действие.
/// \return Информация о действии.
static char* ActionInfo(Action action)
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

/// Вывод стравки
///
static void Help()
{
    for (Action i = ACTION_EXIT; i < ACTION_DEFAULT; i++)
    {
        printf(HELP_ENTER_ACTION, i, ActionInfo(i));
    }
    printf(HELP_COUNT, MAX_COUNT);
    printf(HELP_STRINGS);
}

bool ActionNumberChecker(int number)
{
    return ACTION_EXIT <= number && number < ACTION_DEFAULT;
}

#define ACTION_DEFAULT_RETURN_CODE -1

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
            return ACTION_DEFAULT_RETURN_CODE;
    }
    printf("\n");
    fflush(stdout);
    return 1;
}