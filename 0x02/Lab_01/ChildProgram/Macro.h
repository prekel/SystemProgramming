/*! \file
 *  \brief   Macro
 *
 *  \details Macro-definitions.
 */

#ifndef MACRO_H
#define MACRO_H

#include <stdlib.h>
#include <stdio.h>

/*! \brief Macro for pointer checking for null
 *
 *  \details Program returns EXIT_FAILURE (1) if ptr == NULL. Needed to
 *  check allocated memory using malloc.
 *
 *  \param ptr Pointer to allocated memory for check
 */
#define FAILURE_IF_NULLPTR(ptr) do { \
    if((ptr) == NULL) { \
        fprintf(stderr, "Ошибка при выделении памяти\n"); \
        exit(EXIT_FAILURE); \
    } \
} while(0)

#endif // MACRO_H
