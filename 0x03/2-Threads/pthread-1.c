/*! \file    pthread-1.c
 *  \brief   Print charaters by two threads.
 *
 *  \details Printing y's and e's to stderr.
 *           Second thread's to be created by first thread.
 */

#include <pthread.h>
#include <stdio.h>

/*! \brief Prints y's to stderr
 *
 *  \details Printing y's to stderr.
 *           Does not return due to forever loop inside the function body.
 *
 *  \param unused dummy parameter
 *  \return NULL-pointer
 */

void* printYs(void* unused)
{
  while (!0)
    fputc('y', stderr);
  return NULL;
}

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */

int main()
{
  pthread_t threadId;

  /* Create a new thread.  The new thread will run the printYs
     function.  */
  pthread_create(&threadId, NULL, &printYs, NULL);

  /* Print e's continuously to stderr.  */
  while (!0)
    fputc('e', stderr);
  return 0;
}
