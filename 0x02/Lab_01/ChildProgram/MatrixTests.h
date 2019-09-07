/*! \file    ChildProgram/MatrixTests.h
 *  \brief   Tests for matrix
 *
 *  \details Tests for matrix structure and functions.
 */

#ifndef MATRIXTESTS_H
#define MATRIXTESTS_H

#include <CUnit/Basic.h>

#include "Matrix.h"

/*! \brief Test for create an empty 3x2 Matrix
 */
void Empty3x2_MatrixTest(void);

/*! \brief Test for sum 2x2 Matrix
 */
void Sum2x2_MatrixTest(void);

/*! \brief Test for calculate determinant 2x2 Matrix
 */
void Det2x2_MatrixTest(void);

/*! \brief Test for calculate determinant 3x3 Matrix
 */
void Det3x3_MatrixTest(void);

/*! \brief Test for calculate determinant 7x7 Matrix
 */
void Det7x7_MatrixTest(void);

/*! \brief Test for calculate 2x3 minor for 3x4 Matrix
 */
void Minor3x4_MatrixTest(void);

#endif // MATRIXTESTS_H
