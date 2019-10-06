/// \file
/// \brief Макросы
/// \details Макросы.

#ifndef MACRO_H
#define MACRO_H

#include <stdlib.h>
#include <stdio.h>

/// Макрос для проверки указателя на NULL. Программа аварийно завершается с кодом 0 (EXIT_FAILURE) если ptr == NULL.
/// \param ptr Указатель для проверки
#define FAILURE_IF_NULLPTR(ptr) do { \
    if((ptr) == NULL) { \
        fprintf(stderr, "Ошибка при выделении памяти\n"); \
        exit(EXIT_FAILURE); \
    } \
} while(0)

/// Макрос, формиирующий строку с именем файла (например, для этого файла будет "Macro.h")
#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

/// Макрос нужен для STRINGIZE(A)
#define STRINGIZE_NX(A) #A

/// Макрос преобразующий не-строковое определение в строковое. Например STRINGIZE(__LINE__) будет "26".
/// \param A Определение для преобразования
#define STRINGIZE(A) STRINGIZE_NX(A)

#endif // MACRO_H
