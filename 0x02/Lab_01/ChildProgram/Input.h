/*! \file    ChildProgram/Input.h
 *  \brief   Functions to input with checks
 *
 *  \details Functions to input with checker.
 *  \bug     If input with chars at end, "12fsdf" for example, chars will
 *           be ignored and 12 will be returned in example.
 */

#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

/*! \brief Reads line
 *
 *  \details Reads line.
 *
 *  \param str Pointer to string of line input.
 *  \return String length.
 */
int InputLine(char* str);

/*! \brief Input int with checks.
 *
 *  \details Write output phrase and reads integer with checker and check for
 *  non-number chars at begin.
 *
 * @param output String to output before input.
 * @param checker Pointer to function which check value.
 * @return Read integer.
 */
int CycleInputInt(char* output, bool(* checker)(int));

#endif // INPUT_H
