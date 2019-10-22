#include <CUnit/Basic.h>

#ifndef SUITE_H
#define SUITE_H

CU_pSuite* SuiteCreate(char* name, void (* pAddTests)(CU_pSuite*));

void SuiteDestroy(CU_pSuite* pSuite);

#endif //SUITE_H
