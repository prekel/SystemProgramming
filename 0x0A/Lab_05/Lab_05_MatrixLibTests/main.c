#include <stdlib.h>

#ifdef _MSC_VER
#include <Windows.h>
#elif _WIN32
#include <windows.h>
#endif

#include <CUnit/Basic.h>

#include "Suite.h"
#include "MatrixTests.h"

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    CU_initialize_registry();

    CU_pSuite* ppSuites[] = {
            MatrixTestsSuiteCreate(),
            NULL};

    CU_basic_run_tests();

    CU_cleanup_registry();

    for (int i = 0; ppSuites[i] != NULL; i++)
    {
        SuiteDestroy(ppSuites[i]);
    }

    return CU_get_error();
}
