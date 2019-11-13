/*! \file    mmap-read.c
 *  \brief   Memory mapping demonstration.
 *
 *  \details Interprocess communication via mapped files.
 */
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#define FILE_LENGTH 0x100

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main(int argc, char* const argv[])
{
  int fd;
  void* fileMemory;
  int integer;

  /* Open the file.  */
  fd = open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);

  /* Create the memory-mapping.  */
  fileMemory = mmap(0, FILE_LENGTH, PROT_READ | PROT_WRITE,
                    MAP_SHARED, fd, 0);
  close(fd);

  /* Read the integer, print it out, and double it.  */
  sscanf(fileMemory, "%d", &integer);
  printf("value: %d\n", integer);
  sprintf((char*) fileMemory, "%d\n", 2 * integer);

  /* Release the memory (unnecessary since the program exits).  */
  munmap(fileMemory, FILE_LENGTH);

  return 0;
}
