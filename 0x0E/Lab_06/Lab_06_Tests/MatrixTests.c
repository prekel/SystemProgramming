#include <stdbool.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

#include <CUnit/Basic.h>

#include "MatrixTests.h"
#include "Suite.h"

#include "Matrix.h"
#include "MatrixIO.h"

#define PRINT_COUNTS(pMatrix, m, n) \
do { \
printf("Кол-во строк, все элементы которых различны: %d\n", \
CountDifferentLines(pMatrix, m, n)); \
printf("Кол-во столбцов, все элементы которых различны: %d\n", \
CountDifferentRows(pMatrix, m, n)); \
} while (false) \

#define TEST_PROLOGUE() \
printf("\n ----- %s\n", CU_get_current_test()->pName) \

#define TEST_EPILOGUE() \
printf("\n") \

static void MatrixTestsAddTests(CU_pSuite* pSuite)
{
    CU_ADD_TEST(*pSuite, Test_CountLineRowAndWrite_5x4_0to19);
    CU_ADD_TEST(*pSuite, Test_CountLineRowAndWrite_5x4_All0);
    CU_ADD_TEST(*pSuite, Test_CountLineRowAndWrite_5x4_OneDiff);
    CU_ADD_TEST(*pSuite, Test_CheckLine_1);
    CU_ADD_TEST(*pSuite, Test_CheckRow_1);
    CU_ADD_TEST(*pSuite, Test_CountLineRowAndWrite_1x1_1);
    CU_ADD_TEST(*pSuite, Test_CountLineRowAndWrite_0x0_1);
    CU_ADD_TEST(*pSuite, Test_CountLineRowAndWrite_3x3_Custom1);
    CU_ADD_TEST(*pSuite, Test_CountLineRowAndWrite_3x3_Custom2);
    CU_ADD_TEST(*pSuite, Example_CountLineRowAndWrite_3x6_RandomThrice);
    CU_ADD_TEST(*pSuite, Example_CountLineRowAndWrite_10x15_RandomThrice);
}

CU_pSuite* MatrixTestsSuiteCreate()
{
    return SuiteCreate("MatrixTests", MatrixTestsAddTests);
}

void Test_CountLineRowAndWrite_5x4_0to19()
{
    TEST_PROLOGUE();

    int m = 5;
    int n = 4;
    int* pMatrix = (int*) malloc(m * n * sizeof(int));
    for (int i = 0; i < m * n; i++)
    {
        pMatrix[i] = i;
    }
    CU_ASSERT_EQUAL(CountDifferentLines(pMatrix, m, n), m);
    CU_ASSERT_EQUAL(CountDifferentRows(pMatrix, m, n), n);

    WriteMatrix(pMatrix, m, n);
    PRINT_COUNTS(pMatrix, m, n);

    free(pMatrix);

    TEST_EPILOGUE();
}

void Test_CountLineRowAndWrite_5x4_All0()
{
    TEST_PROLOGUE();

    const int m = 5;
    const int n = 4;
    int pMatrix[m * n];
    for (int i = 0; i < m * n; i++)
    {
        pMatrix[i] = 0;
    }
    CU_ASSERT_EQUAL(CountDifferentLines(pMatrix, m, n), 0);
    CU_ASSERT_EQUAL(CountDifferentRows(pMatrix, m, n), 0);

    WriteMatrix(pMatrix, m, n);
    PRINT_COUNTS(pMatrix, m, n);

    TEST_EPILOGUE();
}

void Test_CountLineRowAndWrite_5x4_OneDiff()
{
    TEST_PROLOGUE();

    const int m = 5;
    const int n = 4;
    int pMatrix[m * n];
    for (int i = 0; i < m * n; i++)
    {
        pMatrix[i] = i;
    }
    for (int i = n; i < m * n; i++)
    {
        if (i % n == 0) continue;
        pMatrix[i] = 0;
    }
    CU_ASSERT_EQUAL(CountDifferentLines(pMatrix, m, n), 1);
    CU_ASSERT_EQUAL(CountDifferentRows(pMatrix, m, n), 1);

    WriteMatrix(pMatrix, m, n);
    PRINT_COUNTS(pMatrix, m, n);

    TEST_EPILOGUE();
}

void Test_CheckLine_1()
{
    TEST_PROLOGUE();

    const int m = 5;
    const int n = 4;
    int pMatrix[m * n];
    for (int i = 0; i < m * n; i++)
    {
        pMatrix[i] = i;
    }
    for (int i = n; i < m * n; i++)
    {
        if (i % n == 0) continue;
        pMatrix[i] = 0;
    }

    CU_ASSERT_TRUE(CheckAllDifferent(pMatrix, 1, n));
    CU_ASSERT_FALSE(CheckAllDifferent(pMatrix + n, 1, n));
    CU_ASSERT_FALSE(CheckAllDifferent(pMatrix + 2 * n, 1, n));
    CU_ASSERT_FALSE(CheckAllDifferent(pMatrix + 3 * n, 1, n));
    CU_ASSERT_FALSE(CheckAllDifferent(pMatrix + 4 * n, 1, n));

    WriteMatrix(pMatrix, m, n);
    PRINT_COUNTS(pMatrix, m, n);

    TEST_EPILOGUE();
}

void Test_CheckRow_1()
{
    TEST_PROLOGUE();

    const int m = 5;
    const int n = 4;
    int pMatrix[m * n];
    for (int i = 0; i < m * n; i++)
    {
        pMatrix[i] = i;
    }
    for (int i = n; i < m * n; i++)
    {
        if (i % n == 0) continue;
        pMatrix[i] = 0;
    }

    CU_ASSERT_TRUE(CheckAllDifferent(pMatrix, n, m));
    CU_ASSERT_FALSE(CheckAllDifferent(pMatrix + 1, n, m));
    CU_ASSERT_FALSE(CheckAllDifferent(pMatrix + 2, n, m));
    CU_ASSERT_FALSE(CheckAllDifferent(pMatrix + 3, n, m));
    CU_ASSERT_FALSE(CheckAllDifferent(pMatrix + 5, n, m));

    WriteMatrix(pMatrix, m, n);
    PRINT_COUNTS(pMatrix, m, n);

    TEST_EPILOGUE();
}

void Test_CountLineRowAndWrite_1x1_1()
{
    TEST_PROLOGUE();

    const int m = 1;
    const int n = 1;

    int pMatrix[1] = {1};

    CU_ASSERT_EQUAL(CountDifferentLines(pMatrix, m, n), 1);
    CU_ASSERT_EQUAL(CountDifferentRows(pMatrix, m, n), 1);

    WriteMatrix(pMatrix, m, n);
    PRINT_COUNTS(pMatrix, m, n);

    TEST_EPILOGUE();
}

void Test_CountLineRowAndWrite_0x0_1()
{
    TEST_PROLOGUE();

    const int m = 0;
    const int n = 0;

    int pMatrix[0] = {};

    CU_ASSERT_EQUAL(CountDifferentLines(pMatrix, m, n), 0);
    CU_ASSERT_EQUAL(CountDifferentRows(pMatrix, m, n), 0);

    WriteMatrix(pMatrix, m, n);
    PRINT_COUNTS(pMatrix, m, n);

    TEST_EPILOGUE();
}

void Test_CountLineRowAndWrite_3x3_Custom1()
{
    TEST_PROLOGUE();

    const int m = 3;
    const int n = 3;

    int pMatrix[9] = {1, -23, 12,
                      23, -23, 123,
                      123, 123, 1};

    CU_ASSERT_EQUAL(CountDifferentLines(pMatrix, m, n), 2);
    CU_ASSERT_EQUAL(CountDifferentRows(pMatrix, m, n), 2);

    WriteMatrix(pMatrix, m, n);
    PRINT_COUNTS(pMatrix, m, n);

    TEST_EPILOGUE();
}


void Test_CountLineRowAndWrite_3x3_Custom2()
{
    TEST_PROLOGUE();

    const int m = 3;
    const int n = 3;

    int pMatrix[9] = {1, -23, 12,
                      23, -23, 123,
                      123, 123, 123};

    CU_ASSERT_EQUAL(CountDifferentLines(pMatrix, m, n), 2);
    CU_ASSERT_EQUAL(CountDifferentRows(pMatrix, m, n), 1);

    WriteMatrix(pMatrix, m, n);
    PRINT_COUNTS(pMatrix, m, n);

    TEST_EPILOGUE();
}

void Example_CountLineRowAndWrite_3x6_RandomThrice()
{
    TEST_PROLOGUE();

    srand(time(0));

    const int m = 3;
    const int n = 6;

    int pMatrix[m * n];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < m * n; j++)
        {
            pMatrix[j] = rand() % 10;
        }
        WriteMatrix(pMatrix, m, n);

        PRINT_COUNTS(pMatrix, m, n);
    }

    TEST_EPILOGUE();
}

void Example_CountLineRowAndWrite_10x15_RandomThrice()
{
    TEST_PROLOGUE();

    srand(time(0));

    const int m = 10;
    const int n = 15;

    int pMatrix[m * n];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < m * n; j++)
        {
            pMatrix[j] = rand() % 90 + 10;
        }
        WriteMatrix(pMatrix, m, n);

        PRINT_COUNTS(pMatrix, m, n);
    }

    TEST_EPILOGUE();
}
