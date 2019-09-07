/*! \file    print-pid.c
 *  \brief   Print process identifiers
 *
 *  \details Print the process (PID) and parent process (PPID) identifiers.
 */
 
#include <stdio.h>
#include <unistd.h>

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */

int main()
{
  printf("The process ID is %d\n", getpid());
  printf("The parent process ID is %d\n", getppid());
  return 0;
}