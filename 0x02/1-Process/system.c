/*! \file    system.c
 *  \brief   Demonstrate system() function
 *
 *  \details List files in working directory via system() function.
 */

#include <stdio.h>
#include <unistd.h>

/*! \brief Main function
 *  \return Exit code returned by system() function.
 */

int main()
{
  int returnValue = system("ls -l /");
  return returnValue;
}