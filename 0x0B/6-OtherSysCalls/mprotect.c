/*! \file    mprotect.c
 *  \brief   Set memory access permissions.
 *
 *  \details Set memory access permissions via mprotect system call
 */
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static int g_AllocSize;
static char* g_Memory;

/*! \brief   Signal handler.
 *
 *  \details Handler function to trap the protected memory access.
 *
 *  \param   signalNumber      bogus parameter in current release
 *
 */
void SegvHandler(int signalNumber) 
{
  printf("memory accessed!\n");
  mprotect(g_Memory, g_AllocSize, PROT_READ | PROT_WRITE);
}  

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main()
{
  int fd;
  struct sigaction sa;

  /* Install segv_handler as the handler for SIGSEGV.  */
  memset(&sa, 0, sizeof (sa));
  sa.sa_handler = &SegvHandler;
  sigaction(SIGSEGV, &sa, NULL);
  
  /* Allocate one page of memory by mapping /dev/zero.  Map the memory
     as write-only, intially.  */
  g_AllocSize = getpagesize();
  fd = open("/dev/zero", O_RDONLY);
  g_Memory = mmap(NULL, g_AllocSize, PROT_WRITE, MAP_PRIVATE, fd, 0);
  close(fd);

  /* Write to the page to obtain a private copy.  */
  g_Memory[0] = 0;

  /* Make the the memory unwritable.  */
  mprotect(g_Memory, g_AllocSize, PROT_NONE);

  /* Write to the allocated memory region.  */
  g_Memory[0] = 1;

  /* All done; unmap the memory.  */
  printf("all done\n");
  munmap(g_Memory, g_AllocSize);
  return 0;
}
