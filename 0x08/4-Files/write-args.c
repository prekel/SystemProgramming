/*! \file    write-args.c
 *  \brief   Write vectored data to file.
 *
 *  \details Write vectored data to the file via writev system call.
 */
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main(int argc, char* argv[])
{
  int fd;
  struct iovec* vec;
  struct iovec* vecNext;
  int i;

  /* We'll need a "buffer" containing a newline character.  Use an
     ordinary char variable for this.  */
  char newline = '\n';

  /* The first command-line argument is the output filename.  */
  char* filename = argv[1];

  /* Skip past the first two elements of the argument list.  Element
     zero is the name of this program, and element one is the output
     filename.  */
  argc -= 2;
  argv += 2;

  /* Allocate an array of iovec elements.  We'll need two for each
     element of the argument list, one for the text itself and one for
     a newline.  */
  vec = (struct iovec*) malloc(2 * argc * sizeof (struct iovec));

  /* Loop over the argument list, building the iovec entries.  */
  vecNext = vec;
  for (i = 0; i < argc; ++i)
  {
    /* The first element is the text of the argument itself.  */
    vecNext->iov_base = argv[i];
    vecNext->iov_len = strlen(argv[i]);
    ++vecNext;

    /* The second element is a single newline character.  It's OK for
       multiple elements of the struct iovec array to point to the
       same region of memory.  */
    vecNext->iov_base = &newline;
    vecNext->iov_len = 1;
    ++vecNext;
  }

  /* Write the arguments to a file.  */
  fd = open(filename, O_WRONLY | O_CREAT);
  writev(fd, vec, 2 * argc);
  close(fd);

  free(vec);
  return 0;
}
