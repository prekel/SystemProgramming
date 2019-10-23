/*! \file    hexdump.c
 *  \brief   File dumping demo.
 *
 *  \details Dumping data from the file via read system call.
 */
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main(int argc, char* argv[])
{
  unsigned char buffer[16];
  size_t offset = 0;
  size_t bytesRead;
  int i;

  /* Open the file for reading.  */
  int fd = open(argv[1], O_RDONLY);
  
  /* Read from the file, one chunk at a time.  Continue until read
     "comes up short", i.e. reads less than we asked for.  This
     indicates that we've hit the end of the file.  */
  do
  {
    /* Read the next lines's worth of bytes.  */
    bytesRead = read(fd, buffer, sizeof (buffer));

    /* Print the offset in the file, followed by the bytes themselves.  */
    printf("0x%06x : ", offset);
    for (i = 0; i < bytesRead; ++i)
      printf ("%02x ", buffer[i]);
    printf ("\n");

    /* Keep count of our position in the file.  */
    offset += bytesRead;
  }
  while (bytesRead == sizeof (buffer));

  /* All done.  */
  close(fd);
  return 0;
}
