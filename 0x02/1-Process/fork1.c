/*! \file    fork1.c
 *  \brief   Fork process.
 *
 *  \details Forking process without its executing.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main()
{
  pid_t childPid;
  
  printf("The main program PID is %d\n", getpid());
  childPid = fork();
  if(0 != childPid)
  {
    printf("This is parent process, its PID is %d\n", getppid());
    printf("The child's PID is %d\n", childPid);
  }
  else
  {
    printf("This is child process, its PID is %d\n", getppid());
  }

  return 0;
}
