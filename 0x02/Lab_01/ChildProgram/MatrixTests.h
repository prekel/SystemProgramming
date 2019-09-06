/*! \file    MatrixTests.h
 *  \brief   Tests for matrix
 *
 *  \details Tests for matrix structure and functions.
 */

#ifndef MATRIXTESTS_H
#define MATRIXTESTS_H

#include <CUnit/Basic.h>

#include "Matrix.h"

/*! \brief Test for create an empty 3x2 matrix
 */
void Empty3x2_MatrixTest(void);

/*! \brief Test for sum 2x2 matrix
 */
void Sum2x2_MatrixTest(void);

/*! \brief Test for calculate determinant 2x2 matrix
 */
void Det2x2_MatrixTest(void);

/*! \brief Test for calculate determinant 3x3 matrix
 */
void Det3x3_MatrixTest(void);

/*! \brief Test for calculate determinant 7x7 matrix
 */
void Det7x7_MatrixTest(void);

#endif // MATRIXTESTS_H
