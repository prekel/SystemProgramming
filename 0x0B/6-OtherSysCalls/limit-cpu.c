/*! \file    limit-cpu.c
 *  \brief   Obtain and set limits to CPU usage.
 *
 *  \details Obtain and set limits
 *           to CPU usage via system calls - getrlimit, setrlimit.
 */
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main()
{
  struct rlimit rl;

  /* Obtain the current limits.  */
  getrlimit(RLIMIT_CPU, &rl);

  /* Set a CPU limit of one second.  */
  rl.rlim_cur = 1;
  setrlimit(RLIMIT_CPU, &rl);

  /* Do busy work.  */
  while (!0)
    ;

  return 0;
}
