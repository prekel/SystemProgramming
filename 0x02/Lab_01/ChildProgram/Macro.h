#ifndef MACRO_H
#define MACRO_H

#include <stdlib.h>

#define FAILURE_IF_NULLPTR(ptr) do { \
    if((ptr) == NULL) { \
        fprintf(stderr, "Ошибка при выделении памяти\n"); \
        exit(EXIT_FAILURE); \
    } \
} while(0)

#endif // MACRO_H
