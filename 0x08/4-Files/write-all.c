/*! \file    write-all.c
 *  \brief   Write data to file code snippet.
 *
 *  \details Code snippet to write data to the file via write system call.
 */
#include <assert.h>
#include <unistd.h>

/*! \brief  Write all bytes to file.
 *
 *  \details Write all of bytes from buffer to file.
 *
 *  \param   fd      File descriptor of opened file. To be closed outside.
 *  \param   buffer  Buffered data to write to file.
 *  \param   count   Data length to write
 *
 *  \return          Number of bytes written
 *                   -1 upon error.
 */
ssize_t WriteAll(int fd, const void* buffer, size_t count)
{
  size_t leftToWrite = count;
  while (leftToWrite > 0)
  {
    size_t written = write(fd, buffer, count);
    if (-1 == written)
      /* An error occurred; bail.  */
      return -1;
    else
      /* Keep count of how much more we need to write.  */
      leftToWrite -= written;
  }

  /* We should have written no more than COUNT bytes!  */
  assert (0 == leftToWrite);

  /* The number of bytes written is exactly COUNT.  */
  return count;
}
