/*! \file    read-file.c
 *  \brief   Get file information code snippet.
 *
 *  \details Code snippet to get file information via stat system call.
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*! \brief  Read the contents of filename into a newly-allocated buffer.
 *
 *  \details Read the contents of filename into a newly-allocated buffer.
 *
 *  \param   filename    Name of a file.
 *  \param   length      The size of the buffer to store filename length.
 *
 *  \return  A pointer to allocated memory area, which the caller must free.
 *           NULL      If filename doesn't correspond to a regular file
 */
char* ReadFile(const char* filename, size_t* length)
{
  int fd;
  struct stat fileInfo;
  char* buffer;

  /* Open the file.  */
  fd = open(filename, O_RDONLY);

  /* Get information about the file.  */
  fstat(fd, &fileInfo);
  *length = fileInfo.st_size;

  /* Make sure the file is an ordinary file.  */
  if (!S_ISREG(fileInfo.st_mode))
  {
    /* It's not, so give up.  */
    close(fd);
    return NULL;
  }

  /* Allocate a buffer large enough to hold the file's contents.  */
  buffer = (char*) malloc(*length);

  /* Read the file into the buffer.  */
  read(fd, buffer, *length);

  /* Finish up.  */
  close(fd);
  return buffer;
}
