/*! \file    itimer.c
 *  \brief   Working with interval timers.
 *
 *  \details Working with interval timers demo code.
 *           Here setitmer system call is used in program.
 */
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

/*! \brief   Timer handler.
 *
 *  \details Handler function to timer expiration.
 *
 *  \param   signum      bogus parameter in current release
 *
 */
void TimerHandler(int signum)
{
  static int count = 0;
  printf("timer expired %d times\n", ++count);
}

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main()
{
  struct sigaction sa;
  struct itimerval timer;

  /* Install timer_handler as the signal handler for SIGVTALRM.  */
  memset (&sa, 0, sizeof (sa));
  sa.sa_handler = &TimerHandler;
  sigaction (SIGVTALRM, &sa, NULL);

  /* Configure the timer to expire after 250 msec...  */
  timer.it_value.tv_sec = 0;
  timer.it_value.tv_usec = 250000;

  /* ... and every 250 msec after that.  */
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 250000;

  /* Start a virtual timer.  It counts down whenever this process is
     executing.  */
  setitimer(ITIMER_VIRTUAL, &timer, NULL);

  /* Do busy work.  */
  while (!0)
    ;
}
