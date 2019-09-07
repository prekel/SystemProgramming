/*! \file    sigchld.c
 *  \brief   Delete child process asynchronously.
 *
 *  \details Code sinppet to delete child process asynchronously
 *           via *NIX signal processing (signal value SIGCHLD)
 */

#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/*! Global variable for exit status of child process */
sig_atomic_t g_ChildExitStatus;

/*! \brief Cleaning up the child process
 *
 *  \details Clean up the child process via signal catching.
 *           Store process's exit status.
 *  \param signalNumber
 *  \return void
 *  \par    Side effect:
 *          changes the g_ChildExitStatus variable
 */

void CleanUpChildProcess(int signalNumber)
{
  /* Clean up the child process.  */
  int status;
  wait(&status);

  /* Store its exit status in a global variable.  */
  g_ChildExitStatus = status;
}

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main()
{
  /* Handle SIGCHLD by calling CleanUpChildProcess. */
  struct sigaction sigchldAction;
  memset (&sigchldAction, 0, sizeof (sigchldAction));
  sigchldAction.sa_handler = &CleanUpChildProcess;
  sigaction(SIGCHLD, &sigchldAction, NULL);

  /* Now do things, including forking a child process.  */
  /* ...  */

  return 0;
}
