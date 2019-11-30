/*! \file    bit-pos-loop.c
 *  \brief   Compute the position of most significant bit in integer.
 *
 *  \details Compute the position of most significant bit in integer using shift
 *           operations within for loop.
 */
#include <stdio.h>
#include <stdlib.h>

/*! \brief Main function
 *
 *  \details Main function is entry point.
 *
 *  \param  argc  The number of command line arguments.
 *  \param  argv  Command line arguments.
 * 
 *  \return 0, upon exit scucces
 */
int main (int argc, char* argv[])
{
  long max = atoi (argv[1]);
  long number;
  long i;
  unsigned position;
  volatile unsigned result;

  /* Repeat the operation for a large number of values.  */
  for (number = 1; number <= max; ++number) {
    /* Repeatedly shift the number to the right, until the result is
       zero.  Keeep count of the number of shifts this requires.  */
    for (i = (number >> 1), position = 0; i != 0; ++position)
      i >>= 1;
    /* The position of the most significant set bit is the number of
       shifts we needed after the first one.  */
    result = position;
  }

  return 0;
}
