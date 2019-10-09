/*! \file    detached.c
 *  \brief   Working with detached thread.
 *
 *  \details Code snippet for detached thread.
 */

#include <pthread.h>

/*! \brief Thread function.
 *
 *  \param threadArg  An argument to the thread function.
 *  \return           NULL.
 */

void* threadFunction(void* threadArg)
{
  /* Do work here...  */
  return NULL;
}

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */

int main()
{
  pthread_attr_t attr;
  pthread_t thread;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  pthread_create(&thread, &attr, &threadFunction, NULL);
  pthread_attr_destroy(&attr);

  /* Do work here...  */

  /* No need to join the second thread.  */
  return 0;
}
