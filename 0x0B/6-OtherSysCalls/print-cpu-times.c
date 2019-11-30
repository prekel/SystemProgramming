/*! \file    print-cpu-times.c
 *  \brief   Print CPU usage time.
 *
 *  \details Print CPU usage time via getrusage system call
 */
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

/*! \brief   Print CPU usage time.
 *
 *  \details Get time spent in CPU system and user mode.
 *
 */
void PrintCpuTime()
{
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  printf("CPU time: %ld.%06ld sec user, %ld.%06ld sec system\n",
	 usage.ru_utime.tv_sec, usage.ru_utime.tv_usec,
	 usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
}
