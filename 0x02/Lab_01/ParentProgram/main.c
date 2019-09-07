/*! \file
 *  \brief   Main file of parent program
 *
 *  \details Main file which contains the main function.
 */

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
pid_t Spawn(char* program, char** argList)
{
    pid_t childPid;

    childPid = fork();

    if (childPid == 0)
    {
        execvp(program, argList);

        fprintf(stderr, "Ошибка при выполнении execvp\n");
        fflush(stderr);
        abort();
    }

    return childPid;
}

/*! \brief Main function
 *
 *  \details Main function. If no argument given, will be exec Child
 *  program via relative path "../ChildProgram/ChildProgram". If arguments
 *  given, will be exec program in argument. Then wait child for exit.
 *
 *  \param argc Count program arguments.
 *  \param argv Array string which contains args.
 *  \return Integer 0 upon exit success.
 */
int main(int argc, char** argv)
{
    char* child = NULL;
    char** argList = NULL;

    if (argc > 1)
    {
        child = argv[1];
        argList = argv + 1;
    } else
    {
        child = "../ChildProgram/ChildProgram";
        char* argListTmp[] = {child, NULL};
        argList = argListTmp;
    }

    int childPid = Spawn(child, argList);
    waitpid(childPid, NULL, 0);

    return 0;
}
