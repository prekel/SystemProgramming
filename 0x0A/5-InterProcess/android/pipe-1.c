/*! \file    pipe-1.c
 *  \brief   Pipe demonstration.
 *
 *  \details Interprocess communication via pipe.
 *           Parent process is writer, and child proccess is reader.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*! \brief Process-writer
 *
 *  \details A process to write copies of message to a stream,
 *           pausing for a second between each.
 *  \param message      Text message
 *  \param count        Number of copies
 *  \param stream       Output stream
 */
void writer(const char* message, int count, FILE* stream)
{
  for (; count > 0; --count)
  {
    /* Write the message to the stream, and send it off immediately.  */
    fprintf(stream, "%s\n", message);
    fflush(stream);

    /* Snooze a while.  */
    sleep(1);
  }
}

/*! \brief Process-reader
 *
 *  \details A process to read random strings from the stream
 *           as long as possible.
 *  \param stream       Input stream
 */
void reader(FILE* stream)
{
  char buffer[1024];

  /* Read until we hit the end of the stream.  fgets reads until
     either a newline or the end-of-file.  */
  while (!feof(stream) 
	 && !ferror(stream) 
	 && fgets(buffer, sizeof (buffer), stream) != NULL
	)
    fputs(buffer, stdout);
}

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
    FILE* stream;

    /* This is the child process.  Close our copy of the write end of
       the file descriptor.  */
    close(fds[1]);

    /* Convert the read file descriptor to a FILE object, and read
       from it.  */
    stream = fdopen(fds[0], "r");
    reader(stream);
    close(fds[0]);
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
    writer("Hello, goodbye and farewell!", 4, stream);
    close(fds[1]);
  }

  return 0;
}
