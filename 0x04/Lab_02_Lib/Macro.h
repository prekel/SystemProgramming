/// \file
/// \brief Макросы
/// \details Макросы.

#ifndef MACRO_H
#define MACRO_H

#include <stdlib.h>
#include <stdio.h>

/// Макрос для провер
/// \param ptr Pointer to allocated memory for check
///
#define FAILURE_IF_NULLPTR(ptr) do { \
    if((ptr) == NULL) { \
        fprintf(stderr, "Ошибка при выделении памяти\n"); \
        exit(EXIT_FAILURE); \
    } \
} while(0)

//#ifdef __MINGW32__
//#define _FILE strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__
//#else
//#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__
//#endif

#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define STRINGIZE_NX(A) #A
#define STRINGIZE(A) STRINGIZE_NX(A)

#endif // MACRO_H
