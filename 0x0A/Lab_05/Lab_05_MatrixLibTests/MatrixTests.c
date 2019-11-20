#include <stdbool.h>

#include <CUnit/Basic.h>

#include "Matrix.h"
#include "MatrixTests.h"
#include "Suite.h"

static void MatrixTestsAddTests(CU_pSuite* pSuite)
{
    CU_ADD_TEST(*pSuite, Blank3x2_MatrixTest);
    CU_ADD_TEST(*pSuite, Det2x2_MatrixTest);
    CU_ADD_TEST(*pSuite, Det3x3_MatrixTest);
    CU_ADD_TEST(*pSuite, Det7x7_MatrixTest);
    CU_ADD_TEST(*pSuite, Minor3x4_MatrixTest);
}

CU_pSuite* MatrixTestsSuiteCreate()
{
    return SuiteCreate("MatrixTests", MatrixTestsAddTests);
}


void Blank3x2_MatrixTest(void)
{
    Matrix* pMatrix = CreateBlankMatrix(3, 2);

    CU_ASSERT_EQUAL(pMatrix->FirstCount, 3);
    CU_ASSERT_EQUAL(pMatrix->SecondCount, 2);

    CU_ASSERT_EQUAL(pMatrix->ppData[0][0], 0);
    CU_ASSERT_EQUAL(pMatrix->ppData[1][1], 0);
    CU_ASSERT_EQUAL(pMatrix->ppData[2][0], 0);
    CU_ASSERT_EQUAL(pMatrix->ppData[0][1], 0);
    CU_ASSERT_EQUAL(pMatrix->ppData[1][0], 0);
    CU_ASSERT_EQUAL(pMatrix->ppData[2][1], 0);

    DestroyMatrix(pMatrix);
}

void Det2x2_MatrixTest(void)
{
    Matrix* pMatrix = CreateBlankMatrix(2, 2);

    pMatrix->ppData[0][0] = 1;
    pMatrix->ppData[0][1] = -65;
    pMatrix->ppData[1][0] = 33;
    pMatrix->ppData[1][1] = -33;

    int det = CalculateDeterminant(pMatrix);
    int det2x2 = CalculateDeterminant2x2(pMatrix);

    CU_ASSERT_EQUAL(det, det2x2);

    CU_ASSERT_EQUAL(det, 2112);

    DestroyMatrix(pMatrix);
}

void Det3x3_MatrixTest(void)
{
    Matrix* pMatrix = CreateBlankMatrix(3, 3);

    pMatrix->ppData[0][0] = 1;
    pMatrix->ppData[0][1] = -65;
    pMatrix->ppData[0][2] = -2;
    pMatrix->ppData[1][0] = 33;
    pMatrix->ppData[1][1] = -33;
    pMatrix->ppData[1][2] = -6;
    pMatrix->ppData[2][0] = 33;
    pMatrix->ppData[2][1] = 4;
    pMatrix->ppData[2][2] = -65;

    int det = CalculateDeterminant(pMatrix);

    CU_ASSERT_EQUAL(det, -126828);

    DestroyMatrix(pMatrix);
}

void Det7x7_MatrixTest(void)
{
    Matrix* pMatrix = CreateBlankMatrix(7, 7);

    pMatrix->ppData[0][0] = 1;
    pMatrix->ppData[0][1] = 6;
    pMatrix->ppData[0][2] = -2;
    pMatrix->ppData[0][3] = 2;
    pMatrix->ppData[0][4] = 1;
    pMatrix->ppData[0][5] = 6;
    pMatrix->ppData[0][6] = 2;

    pMatrix->ppData[1][0] = 3;
    pMatrix->ppData[1][1] = 3;
    pMatrix->ppData[1][2] = 6;
    pMatrix->ppData[1][3] = 3;
    pMatrix->ppData[1][4] = 3;
    pMatrix->ppData[1][5] = -6;
    pMatrix->ppData[1][6] = 6;

    pMatrix->ppData[2][0] = 3;
    pMatrix->ppData[2][1] = -4;
    pMatrix->ppData[2][2] = 6;
    pMatrix->ppData[2][3] = 3;
    pMatrix->ppData[2][4] = 4;
    pMatrix->ppData[2][5] = 6;
    pMatrix->ppData[2][6] = 3;

    pMatrix->ppData[3][0] = -3;
    pMatrix->ppData[3][1] = 4;
    pMatrix->ppData[3][2] = -6;
    pMatrix->ppData[3][3] = 3;
    pMatrix->ppData[3][4] = 4;
    pMatrix->ppData[3][5] = -6;
    pMatrix->ppData[3][6] = 3;

    pMatrix->ppData[4][0] = 3;
    pMatrix->ppData[4][1] = -3;
    pMatrix->ppData[4][2] = 6;
    pMatrix->ppData[4][3] = 3;
    pMatrix->ppData[4][4] = -3;
    pMatrix->ppData[4][5] = 6;
    pMatrix->ppData[4][6] = 6;

    pMatrix->ppData[5][0] = 1;
    pMatrix->ppData[5][1] = 6;
    pMatrix->ppData[5][2] = 2;
    pMatrix->ppData[5][3] = -2;
    pMatrix->ppData[5][4] = 1;
    pMatrix->ppData[5][5] = 6;
    pMatrix->ppData[5][6] = 2;

    pMatrix->ppData[6][0] = 1;
    pMatrix->ppData[6][1] = 6;
    pMatrix->ppData[6][2] = 2;
    pMatrix->ppData[6][3] = 2;
    pMatrix->ppData[6][4] = 1;
    pMatrix->ppData[6][5] = 6;
    pMatrix->ppData[6][6] = 2;

    int det = CalculateDeterminant(pMatrix);

    CU_ASSERT_EQUAL(det, 355968);

    DestroyMatrix(pMatrix);
}

void Minor3x4_MatrixTest(void)
{
    Matrix* pMatrix = CreateBlankMatrix(3, 4);

    pMatrix->ppData[0][0] = 1;
    pMatrix->ppData[0][1] = 2;
    pMatrix->ppData[0][2] = 3;
    pMatrix->ppData[0][3] = 4;

    pMatrix->ppData[1][0] = 5;
    pMatrix->ppData[1][1] = 6;
    pMatrix->ppData[1][2] = 7;
    pMatrix->ppData[1][3] = 8;

    pMatrix->ppData[2][0] = 9;
    pMatrix->ppData[2][1] = 10;
    pMatrix->ppData[2][2] = 11;
    pMatrix->ppData[2][3] = 12;

    Matrix* pMinor1 = GetMinor(NULL, pMatrix, 0, 0);

    CU_ASSERT_EQUAL(pMinor1->FirstCount, 2);
    CU_ASSERT_EQUAL(pMinor1->SecondCount, 3);
    CU_ASSERT_EQUAL(pMinor1->ppData[0][0], 6);
    CU_ASSERT_EQUAL(pMinor1->ppData[0][1], 7);
    CU_ASSERT_EQUAL(pMinor1->ppData[0][2], 8);
    CU_ASSERT_EQUAL(pMinor1->ppData[1][0], 10);
    CU_ASSERT_EQUAL(pMinor1->ppData[1][1], 11);
    CU_ASSERT_EQUAL(pMinor1->ppData[1][2], 12);

    Matrix* pMinor2 = GetMinor(NULL, pMatrix, 1, 1);

    CU_ASSERT_EQUAL(pMinor2->FirstCount, 2);
    CU_ASSERT_EQUAL(pMinor2->SecondCount, 3);
    CU_ASSERT_EQUAL(pMinor2->ppData[0][0], 1);
    CU_ASSERT_EQUAL(pMinor2->ppData[0][1], 3);
    CU_ASSERT_EQUAL(pMinor2->ppData[0][2], 4);
    CU_ASSERT_EQUAL(pMinor2->ppData[1][0], 9);
    CU_ASSERT_EQUAL(pMinor2->ppData[1][1], 11);
    CU_ASSERT_EQUAL(pMinor2->ppData[1][2], 12);

    Matrix* pMinor3 = GetMinor(NULL, pMatrix, 2, 3);

    CU_ASSERT_EQUAL(pMinor3->FirstCount, 2);
    CU_ASSERT_EQUAL(pMinor3->SecondCount, 3);
    CU_ASSERT_EQUAL(pMinor3->ppData[0][0], 1);
    CU_ASSERT_EQUAL(pMinor3->ppData[0][1], 2);
    CU_ASSERT_EQUAL(pMinor3->ppData[0][2], 3);
    CU_ASSERT_EQUAL(pMinor3->ppData[1][0], 5);
    CU_ASSERT_EQUAL(pMinor3->ppData[1][1], 6);
    CU_ASSERT_EQUAL(pMinor3->ppData[1][2], 7);

    Matrix* pMinor4 = GetMinor(NULL, pMatrix, 2, 1);

    CU_ASSERT_EQUAL(pMinor4->FirstCount, 2);
    CU_ASSERT_EQUAL(pMinor4->SecondCount, 3);
    CU_ASSERT_EQUAL(pMinor4->ppData[0][0], 1);
    CU_ASSERT_EQUAL(pMinor4->ppData[0][1], 3);
    CU_ASSERT_EQUAL(pMinor4->ppData[0][2], 4);
    CU_ASSERT_EQUAL(pMinor4->ppData[1][0], 5);
    CU_ASSERT_EQUAL(pMinor4->ppData[1][1], 7);
    CU_ASSERT_EQUAL(pMinor4->ppData[1][2], 8);

    DestroyMatrix(pMatrix);
    DestroyMatrix(pMinor1);
    DestroyMatrix(pMinor2);
    DestroyMatrix(pMinor3);
    DestroyMatrix(pMinor4);
}
