#include <stdbool.h>

#include <CUnit/Basic.h>

#include "ArchipelagoCollection.h"
#include "ArchipelagoCollectionQuery.h"
#include "Archipelago.h"

#include "Suite.h"
#include "ArchipelagoCollectionQueryTests.h"

static void ArchipelagoCollectionQueryTestsAddTests(CU_pSuite* pSuite)
{
    CU_ADD_TEST(*pSuite, ArchipelagoCollectionQueryTest_HasOnlyUninhabited1);
    CU_ADD_TEST(*pSuite, ArchipelagoCollectionQueryTest_HasOnlyUninhabited2);
    CU_ADD_TEST(*pSuite, ArchipelagoCollectionQueryTest_SelectWhereIslandsCountIs1);
}

CU_pSuite* ArchipelagoCollectionQueryTestsSuiteCreate()
{
    return SuiteCreate("ArchipelagoCollectionTests",
                       ArchipelagoCollectionQueryTestsAddTests);
}

#define HasOnlyUninhabited1_NAME "name1"
#define HasOnlyUninhabited1_NAMELEN 5
#define HasOnlyUninhabited1_COUNT 12
#define HasOnlyUninhabited1_COUNTINH 3

#define HasOnlyUninhabited1_NAME2 "имя2"
#define HasOnlyUninhabited1_NAMELEN2 7
#define HasOnlyUninhabited1_COUNT2 132
#define HasOnlyUninhabited1_COUNTINH2 3

void ArchipelagoCollectionQueryTest_HasOnlyUninhabited1(void)
{
    ArchipelagoCollection* pCollection = ArchipelagoCollectionCreate();
    CU_ASSERT_FALSE(
            ArchipelagoCollectionQueryHasOnlyUninhabited(pCollection));

    ArchipelagoCollectionAdd(pCollection,
                             ArchipelagoCreate(HasOnlyUninhabited1_NAME,
                                               HasOnlyUninhabited1_COUNT,
                                               HasOnlyUninhabited1_COUNTINH));
    CU_ASSERT_FALSE(
            ArchipelagoCollectionQueryHasOnlyUninhabited(pCollection));

    ArchipelagoCollectionAdd(pCollection,
                             ArchipelagoCreate(HasOnlyUninhabited1_NAME2,
                                               HasOnlyUninhabited1_COUNT2,
                                               HasOnlyUninhabited1_COUNTINH2));
    CU_ASSERT_FALSE(
            ArchipelagoCollectionQueryHasOnlyUninhabited(pCollection));

    ArchipelagoCollectionDestroyArchipelagos(pCollection);
    ArchipelagoCollectionDestroy(pCollection);
}

#define HasOnlyUninhabited2_NAME "name1"
#define HasOnlyUninhabited2_NAMELEN 5
#define HasOnlyUninhabited2_COUNT 12
#define HasOnlyUninhabited2_COUNTINH 3

#define HasOnlyUninhabited2_NAME2 "имя2"
#define HasOnlyUninhabited2_NAMELEN2 7
#define HasOnlyUninhabited2_COUNT2 132
#define HasOnlyUninhabited2_COUNTINH2 0

void ArchipelagoCollectionQueryTest_HasOnlyUninhabited2(void)
{
    ArchipelagoCollection* pCollection = ArchipelagoCollectionCreate();
    CU_ASSERT_FALSE(
            ArchipelagoCollectionQueryHasOnlyUninhabited(pCollection));

    ArchipelagoCollectionAdd(pCollection,
                             ArchipelagoCreate(HasOnlyUninhabited2_NAME,
                                               HasOnlyUninhabited2_COUNT,
                                               HasOnlyUninhabited2_COUNTINH));
    CU_ASSERT_FALSE(
            ArchipelagoCollectionQueryHasOnlyUninhabited(pCollection));

    ArchipelagoCollectionAdd(pCollection,
                             ArchipelagoCreate(HasOnlyUninhabited2_NAME2,
                                               HasOnlyUninhabited2_COUNT2,
                                               HasOnlyUninhabited2_COUNTINH2));
    CU_ASSERT_TRUE(ArchipelagoCollectionQueryHasOnlyUninhabited(pCollection));

    ArchipelagoCollectionDestroyArchipelagos(pCollection);
    ArchipelagoCollectionDestroy(pCollection);
}

#define SelectWhereIslandsCountIs1_NAME "name1"
#define SelectWhereIslandsCountIs1_NAMELEN 5
#define SelectWhereIslandsCountIs1_COUNT 12
#define SelectWhereIslandsCountIs1_COUNTINH 3

#define SelectWhereIslandsCountIs1_NAME2 "имя2"
#define SelectWhereIslandsCountIs1_NAMELEN2 7
#define SelectWhereIslandsCountIs1_COUNT2 132
#define SelectWhereIslandsCountIs1_COUNTINH2 3

#define SelectWhereIslandsCountIs1_NAME3 "name3"
#define SelectWhereIslandsCountIs1_NAMELEN3 5
#define SelectWhereIslandsCountIs1_COUNT3 132
#define SelectWhereIslandsCountIs1_COUNTINH3 3

#define SelectWhereIslandsCountIs1_WHERECOUNT1 132
#define SelectWhereIslandsCountIs1_WHERECOUNT2 12
#define SelectWhereIslandsCountIs1_WHERECOUNT3 11

#define SelectWhereIslandsCountIs1_SELECTCOUNT1 2
#define SelectWhereIslandsCountIs1_SELECTCOUNT2 1
#define SelectWhereIslandsCountIs1_SELECTCOUNT3 0

void ArchipelagoCollectionQueryTest_SelectWhereIslandsCountIs1(void)
{
    ArchipelagoCollection* pCollection = ArchipelagoCollectionCreate();
    ArchipelagoCollection* pCollectionQ1;
    ArchipelagoCollection* pCollectionQ2;
    ArchipelagoCollection* pCollectionQ3;

    pCollectionQ1 = ArchipelagoCollectionQuerySelectWhereIslandsCountIs(
            pCollection, SelectWhereIslandsCountIs1_WHERECOUNT1);
    pCollectionQ2 = ArchipelagoCollectionQuerySelectWhereIslandsCountIs(
            pCollection, SelectWhereIslandsCountIs1_WHERECOUNT2);
    pCollectionQ3 = ArchipelagoCollectionQuerySelectWhereIslandsCountIs(
            pCollection, SelectWhereIslandsCountIs1_WHERECOUNT3);
    CU_ASSERT_EQUAL(pCollectionQ1->pList->Count, 0);
    CU_ASSERT_EQUAL(pCollectionQ2->pList->Count, 0);
    CU_ASSERT_EQUAL(pCollectionQ3->pList->Count, 0);
    ArchipelagoCollectionDestroy(pCollectionQ1);
    ArchipelagoCollectionDestroy(pCollectionQ2);
    ArchipelagoCollectionDestroy(pCollectionQ3);

    Archipelago* pArchipelago1 = ArchipelagoCreate(
            SelectWhereIslandsCountIs1_NAME,
            SelectWhereIslandsCountIs1_COUNT,
            SelectWhereIslandsCountIs1_COUNTINH);
    ArchipelagoCollectionAdd(pCollection,
                             pArchipelago1);
    Archipelago* pArchipelago2 = ArchipelagoCreate(
            SelectWhereIslandsCountIs1_NAME2,
            SelectWhereIslandsCountIs1_COUNT2,
            SelectWhereIslandsCountIs1_COUNTINH2);
    ArchipelagoCollectionAdd(pCollection,
                             pArchipelago2);
    Archipelago* pArchipelago3 = ArchipelagoCreate(
            SelectWhereIslandsCountIs1_NAME3,
            SelectWhereIslandsCountIs1_COUNT3,
            SelectWhereIslandsCountIs1_COUNTINH3);
    ArchipelagoCollectionAdd(pCollection,
                             pArchipelago3);
    pCollectionQ1 = ArchipelagoCollectionQuerySelectWhereIslandsCountIs(
            pCollection, SelectWhereIslandsCountIs1_WHERECOUNT1);
    pCollectionQ2 = ArchipelagoCollectionQuerySelectWhereIslandsCountIs(
            pCollection, SelectWhereIslandsCountIs1_WHERECOUNT2);
    pCollectionQ3 = ArchipelagoCollectionQuerySelectWhereIslandsCountIs(
            pCollection, SelectWhereIslandsCountIs1_WHERECOUNT3);
    CU_ASSERT_EQUAL(pCollectionQ1->pList->Count,
                    SelectWhereIslandsCountIs1_SELECTCOUNT1);
    CU_ASSERT_EQUAL(pCollectionQ2->pList->Count,
                    SelectWhereIslandsCountIs1_SELECTCOUNT2);
    CU_ASSERT_EQUAL(pCollectionQ3->pList->Count,
                    SelectWhereIslandsCountIs1_SELECTCOUNT3);

    CU_ASSERT_PTR_EQUAL(pCollectionQ1->pList->pFirst->pElement, pArchipelago2);
    CU_ASSERT_PTR_EQUAL(pCollectionQ1->pList->pLast->pElement, pArchipelago3);

    CU_ASSERT_PTR_EQUAL(pCollectionQ2->pList->pFirst->pElement, pArchipelago1);

    ArchipelagoCollectionDestroy(pCollectionQ1);
    ArchipelagoCollectionDestroy(pCollectionQ2);
    ArchipelagoCollectionDestroy(pCollectionQ3);

    ArchipelagoCollectionDestroyArchipelagos(pCollection);
    ArchipelagoCollectionDestroy(pCollection);
}

