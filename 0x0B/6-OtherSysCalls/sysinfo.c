/*! \file    sysinfo.c
 *  \brief   Get system statistics.
 *
 *  \details Get system statistics via sysinfo system call
 */
#include <linux/kernel.h>
#include <linux/sys.h>
#include <stdio.h>
#include <sys/sysinfo.h>

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main()
{
  /* Conversion constants.  */
  const long minute = 60;
  const long hour = minute * 60;
  const long day = hour * 24;
  const double megabyte = 1024 * 1024;

  /* Obtain system statistics.  */
  struct sysinfo si;
  sysinfo (&si);

  /* Summarize intersting values.  */
  printf("system uptime : %ld days, %ld:%02ld:%02ld\n", 
	 si.uptime / day, (si.uptime % day) / hour, 
	 (si.uptime % hour) / minute, si.uptime % minute);
  printf("total RAM     : %5.1f MB\n", si.totalram / megabyte);
  printf("free RAM      : %5.1f MB\n", si.freeram / megabyte);
  printf("process count : %d\n", si.procs);

  return 0;
}