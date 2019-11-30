/*! \file    copy.c
 *  \brief   Fast file transfer.
 *
 *  \details Fast file transfer via sendfile system call.
 */
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*! \brief Main function
 *
 *  \param  argc   Argument count
 *  \param  argv   Command line arguments
 *
 *  \return Integer 0 upon exit success
 */
int main(int argc, char* argv[])
{
  int read_fd;
  int write_fd;
  struct stat statBuf;
  off_t offset = 0;

  /* Open the input file.  */
  read_fd = open(argv[1], O_RDONLY);

  /* Stat the input file to obtain its size.  */
  fstat(read_fd, &statBuf);

  /* Open the ouput file for writing, with the same permissions as the
     source file.  */
  write_fd = open(argv[2], O_WRONLY | O_CREAT, statBuf.st_mode);

  /* Blast the bytes from one file to the other.  */
  sendfile(write_fd, read_fd, &offset, statBuf.st_size);

  /* Close up.  */
  close(read_fd);
  close(write_fd);

  return 0;
}
