/*! \file    check-access.c
 *  \brief   Checking for access to a file.
 *
 *  \details Checking for access to a file using access system call.
 */
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main(int argc, char* argv[])
{
  char* path = argv[1];
  int rval;

  /* Check file existence.  */
  rval = access(path, F_OK);
  if (0 == rval) 
    printf("%s exists\n", path);
  else {
    if (errno == ENOENT) 
      printf("%s does not exist\n", path);
    else if (errno == EACCES) 
      printf("%s is not accessible\n", path);
    return 0;
  }

  /* Check read access.  */
  rval = access(path, R_OK);
  if (0 == rval)
    printf("%s is readable\n", path);
  else
    printf("%s is not readable (access denied)\n", path);

  /* Check write access.  */
  rval = access(path, W_OK);
  if (rval == 0)
    printf("%s is writable\n", path);
  else if (errno == EACCES)
    printf("%s is not writable (access denied)\n", path);
  else if (errno == EROFS)
    printf("%s is not writable (read-only filesystem)\n", path);

  return 0;
}
