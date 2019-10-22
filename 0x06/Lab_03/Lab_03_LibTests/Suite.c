#include <stdbool.h>
#include <malloc.h>

#include <CUnit/Basic.h>

#include "Suite.h"

CU_pSuite* SuiteCreate(char* name, void (* pAddTests)(CU_pSuite*))
{
    CU_pSuite* pSuite = (CU_pSuite*) malloc(sizeof(CU_pSuite));
    *pSuite = CU_add_suite(name, NULL, NULL);
    pAddTests(pSuite);
    return pSuite;
}

void SuiteDestroy(CU_pSuite* pSuite)
{
    free(pSuite);
}
