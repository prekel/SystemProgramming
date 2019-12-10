/// \file
/// \brief Набор тестов матрицы
/// \details Набор тестов матрицы.

#ifndef MATRIXTESTS_H
#define MATRIXTESTS_H

#include <CUnit/Basic.h>

CU_pSuite* MatrixTestsSuiteCreate();

void Test_CountLineRowAndWrite_5x4_0to19();

void Test_CountLineRowAndWrite_5x4_All0();

void Test_CountLineRowAndWrite_5x4_OneDiff();

void Test_CheckLines_5x4_1();

void Test_CheckLine5_Custom();

void Test_CheckLine4_Custom();

void Test_CheckRows_5x4_1();

void Test_CountLineRowAndWrite_1x1_1();

void Test_CountLineRowAndWrite_0x0_1();

void Test_CountLineRowAndWrite_3x3_Custom1();

void Test_CountLineRowAndWrite_3x3_Custom2();

void Example_CountLineRowAndWrite_3x6_RandomThrice();

void Example_CountLineRowAndWrite_10x15_RandomThrice();

#endif //MATRIXTESTS_H

