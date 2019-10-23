/*! \file    print-symlink.c
 *  \brief   Print symlink info.
 *
 *  \details Printing out the information about symlink.
 */
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

/*! \brief Main function
 *  \return Integer 0 upon exit success
 *          Integer 1 upon error
 */
int main(int argc, char* argv[])
{
  char targetPath[256];
  char* linkPath = argv[1];

  /* Attempt to read the target of the symbolic link.  */
  int len = readlink(linkPath, targetPath, sizeof (targetPath) - 1);

  if (len == -1)
  {
    /* The call failed.  */
    if (errno == EINVAL)
      /* It's not a symbolic link; report that.  */
      fprintf(stderr, "%s is not a symbolic link\n", linkPath);
    else
      /* Some other problem occurred; print the generic message.  */
      perror("readlink");
    return 1;
  }
  else
  {
    /* NUL-terminate the target path.  */
    targetPath[len] = '\0';

    /* Print it.  */
    printf("%s\n", targetPath);
    return 0;
  }
}
