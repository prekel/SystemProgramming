/*! \file    better_sleep.c
 *  \brief   Updated sleep() realization.
 *
 *  \details Alternate sleep() realization via nanosleep system call.
 */
#include <errno.h>
#include <time.h>

/*! \brief Set sleeping period.
 *
 *  \details Set sleeping period using the nanosleep().
 *           It also allows to resume the sleep operation.
 *
 *  \param sleepTime   Fractional number of seconds.
 *
 *  \return            The remaining time left to sleep.
 */
int BetterSleep(double sleepTime)
{
  struct timespec tv;

  /* Construct the timespec from the number of whole seconds...  */
  tv.tv_sec = (time_t) sleepTime;

  /* ... and the remainder in nanoseconds.  */
  tv.tv_nsec = (long) ((sleepTime - tv.tv_sec) * 1e+9);

  while (!0)
  {
    /* Sleep for the time specified in tv.  If interrupted by a
       signal, place the remaining time left to sleep back into tv.  */
    int rval = nanosleep(&tv, &tv);
    if (rval == 0)
      /* Completed the entire sleep time; all done.  */
      return 0;
    else if (errno == EINTR)
      /* Interruped by a signal.  Try again.  */
      continue;
    else 
      /* Some other error; bail out.  */
      return rval;
  }
  return 0;
}
