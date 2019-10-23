/*! \file    timestamp.c
 *  \brief   Write current date and time to file.
 *
 *  \details Write current date and time to file via write system call.
 */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

/*! \brief  Get string with the current date and time.
 *
 *  \details Return character string representing the current date and time.
 *
 *  \return  Character string representing the current date and time.
 */
char* GetTimestamp()
{
  time_t now = time(NULL);
  return asctime(localtime(&now));
}

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main(int argc, char* argv[])
{
  /* The file to which to append the timestamp.  */
  char* filename = argv[1];

  /* Get the current timestamp.  */
  char* timestamp = GetTimestamp ();

  /* Open the file for writing.  If it exists, append to it;
     otherwise, create a new file.  */
  int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);

  /* Compute the length of the timestamp string.  */
  size_t length = strlen(timestamp);

  /* Write the timestamp to the file.  */
  write(fd, timestamp, length);

  /* All done.  */
  close (fd);
  return 0;
}
