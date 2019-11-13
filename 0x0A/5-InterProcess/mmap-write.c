/*! \file    mmap-write.c
 *  \brief   Memory mapping demonstration.
 *
 *  \details Interprocess communication via mapped files.
 */
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#define FILE_LENGTH 0x100

/*! \brief Get a random number.
 *
 *  \details Get a uniformly random number in the range [low,high].
 *
 *  \param low      Lower bound of the range.
 *  \param high     Upper bound of the range.
 *
 *  \return         Random number in the range.
 */
int RandomRange(unsigned const low, unsigned const high)
{
  unsigned const range = high - low + 1;
  return low + (int) (((double) range) * rand() / (RAND_MAX + 1.0));
}

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main(int argc, char* const argv[])
{
  int fd;
  void* fileMemory;

  /* Seed the random number generator.  */
  srand(time(NULL));

  /* Prepare a file large enough to hold an unsigned integer.  */
  fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  lseek(fd, FILE_LENGTH+1, SEEK_SET);
  write(fd, "", 1);
  lseek(fd, 0, SEEK_SET);

  /* Create the memory-mapping.  */
  fileMemory = mmap(0, FILE_LENGTH, PROT_WRITE, MAP_SHARED, fd, 0);
  close(fd);

  /* Write a random integer to memory-mapped area.  */
  sprintf((char*) fileMemory, "%d\n", RandomRange(-100, 100));

  /* Release the memory (unnecessary since the program exits).  */
  munmap(fileMemory, FILE_LENGTH);

  return 0;
}
