/*! \file    print-uname.c
 *  \brief   Get system information.
 *
 *  \details Get system information (OS, machine etc) via uname system call
 */
#include <stdio.h>
#include <sys/utsname.h>

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main()
{
  struct utsname u;
  uname(&u);
  printf("%s release %s (version %s) on %s\n", u.sysname, u.release, 
	 u.version, u.machine);
  return 0;
}
