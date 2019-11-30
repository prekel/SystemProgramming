/*! \file    pipe-2.c
 *  \brief   Pipe demonstration.
 *
 *  \details Interprocess communication via pipe.
 *           Parent process is writer, and child proccess ("sort") is reader.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main()
{
  int fds[2];
  pid_t pid;

  /* Create a pipe.  File descriptors for the two ends of the pipe are
     placed in fds.  */
  pipe(fds);

  /* Fork a child process.  */
  pid = fork();
  if (pid == (pid_t) 0)
  {
    /* This is the child process.  Close our copy of the write end of
       the file descriptor.  */
    close(fds[1]);

    /* Connect the read end of the pipe to standard input.  */
    dup2(fds[0], STDIN_FILENO);

    /* Replace the child process with the "sort" program.  */
    execlp("sort", "sort", 0);
  }
  else
  {
    /* This is the parent process.  */
    FILE* stream;

    /* Close our copy of the read end of the file descriptor.  */
    close(fds[0]);

    /* Convert the write file descriptor to a FILE object, and write
       to it.  */
    stream = fdopen(fds[1], "w");

    fprintf(stream, "3. I don't know what it is that I like about you, but I like it a lot.\n");
    fprintf(stream, "1. Hey, girl, stop what you're doin'!\n");
    fprintf(stream, "5. Communication Breakdown, It's always the same,\n");
    fprintf(stream, "2. Hey, girl, you'll drive me to ruin.\n");
    fprintf(stream, "6. I'm having a nervous breakdown, Drive me insane!\n");
    fprintf(stream, "4. Won't let me hold you, Let me feel your lovin' charms.\n");
    fflush(stream);
    close(fds[1]);

    /* Wait for the child process to finish.  */
    waitpid(pid, NULL, 0);
  }

  return 0;
}
