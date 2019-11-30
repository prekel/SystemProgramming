/*! \file    bit-pos-asm.c
 *  \brief   Compute the position of most significant bit in integer.
 *
 *  \details Compute the position of most significant bit in integer using 
 *           spesific operation code inside inline assembly.
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
  unsigned position;
  volatile unsigned result;

  /* Repeat the operation for a large number of values.  */
  for (number = 1; number <= max; ++number)
  {
    /* Compute the position of the most significant set bit using the
       bsrl assembly instruction.  */
    asm("bsrl %1, %0" : "=r" (position) : "r" (number));
    result = position;
  }

  return 0;
}
