/*! \file    print-time.c
 *  \brief   Print system date and time.
 *
 *  \details Get system date and time, print it in given format.
 *           It uses gettimeofday system call
 */
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

/*! \brief   Print system date and time.
 *
 *  \details Get system date and time with milliseconds.
 *
 */
void PrintTime()
{
  struct timeval tv;
  struct tm* ptm;
  char timeString[40];
  long milliseconds;

  /* Obtain the time of day, and convert it to a tm struct.  */
  gettimeofday(&tv, NULL);
  ptm = localtime(&tv.tv_sec);

  /* Format the date and time, down to a single second.  */
  strftime(timeString, sizeof (timeString), "%Y-%m-%d %H:%M:%S", ptm);

  /* Compute milliseconds from microseconds.  */
  milliseconds = tv.tv_usec / 1000;

  /* Print the formatted time, in seconds, followed by a decimal point
     and the milliseconds.  */
  printf("%s.%03ld\n", timeString, milliseconds);
}
