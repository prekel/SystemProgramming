/*! \file    zombie.c
 *  \brief   Zombie process.
 *
 *  \details Forking child process without its executing and waiting.
 *           Parent process sleeps 'til one minute pause finished.
 */
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main()
{
  pid_t childPid;

  /* Create a child process.  */
  childPid = fork();
  if (childPid > 0)
  {
    /* This is the parent process.  Sleep for a minute. */
    sleep(60);
  }
  else
  {
    /* This is the child process.  Exit immediately.  */
    exit(0);
  }
  return 0;
}
