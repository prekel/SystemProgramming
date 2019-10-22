#ifndef ARCHIPELAGOCOLLECTIONQUERYTESTS_H
#define ARCHIPELAGOCOLLECTIONQUERYTESTS_H

#include <CUnit/Basic.h>

CU_pSuite* ArchipelagoCollectionQueryTestsSuiteCreate();

void ArchipelagoCollectionQueryTest_HasOnlyUninhabited1(void);

void ArchipelagoCollectionQueryTest_HasOnlyUninhabited2(void);

void ArchipelagoCollectionQueryTest_SelectWhereIslandsCountIs1(void);

#endif //ARCHIPELAGOCOLLECTIONQUERYTESTS_H
