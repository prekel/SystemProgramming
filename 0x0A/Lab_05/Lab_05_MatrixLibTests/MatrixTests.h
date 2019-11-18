#ifndef MATRIXTESTS_H
#define MATRIXTESTS_H

#include <CUnit/Basic.h>

CU_pSuite* MatrixTestsSuiteCreate();

void Blank3x2_MatrixTest(void);

void Det2x2_MatrixTest(void);

void Det3x3_MatrixTest(void);

void Det7x7_MatrixTest(void);

void Minor3x4_MatrixTest(void);


#endif //MATRIXTESTS_H

