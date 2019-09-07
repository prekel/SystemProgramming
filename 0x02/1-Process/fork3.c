/*! \file    fork3.c
 *  \brief   Fork, exec and wait process.
 *
 *  \details Forking child process with its executing followed by its waiting.
 *           Child process is a list of files via running "ls" command.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

/*! \brief Spawn a child process
 *
 *  \details Spawn a child process running a new program, as given by PROGRAM.
 *
 *  \param program    The name of the program to runs;
 *                    the path will be searched for this program.
 *  \param argList    A NULL-terminated list of character strings to be
 *                    passed as the program's argument list.
 *  \return           Identifier of the spawned process.
 */

int spawn(char* program, char** argList)
{
  pid_t childPid;

  /* Duplicate this process.  */
  childPid = fork();
  if (0 != childPid)
  {
    /* This is the parent process.  */
    return childPid;
  }
  else
  {
    /* Now execute PROGRAM, searching for it in the path. */
    execvp(program, argList);

    /* The execvp function returns only if an error occurs.  */
    fprintf(stderr, "an error occurred in execvp\n");
    abort();
  }
}

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */

int main()
{
  int childStatus;
  
  /* The argument list to pass to the "ls" command.  */
  char* argList[] =
  {
    "ls",     /* argv[0], the name of the program.  */
    "-l", 
    "/",
    NULL      /* The argument list must end with a NULL.  */
  };

  /* Spawn a child process running the "ls" command.  Ignore the
     returned child process id.  */
  spawn("ls", argList);

  /* Wait for child process  */
  wait(&childStatus);
  if(WIFEXITED(childStatus))
  {
    printf("The child process exited normally with code %d.\n"
           , WEXITSTATUS(childStatus)
          );
  }
  else
  {
    printf("The child process exited abnormally.\n");
  }
  return 0;
}
