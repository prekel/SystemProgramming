#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

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
    } else
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
int main(int argc, char** argv)
{
    char* child = NULL;
    if (argc == 2)
    {
        child = argv[1];
    } else {
        child = "../ChildProgram/ChildProgram";
    }

    int childpid = spawn(child, NULL);
    waitpid(childpid, NULL, 0);

    return 0;
}
