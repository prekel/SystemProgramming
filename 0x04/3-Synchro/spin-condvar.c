/*! \file    spin-condvar.c
 *  \brief   Simplest condvar realization.
 *
 *  \details A code snippet for mutexes as condvars.
 */

#include <pthread.h>

extern void DoWork();

int g_ThreadFlag;
pthread_mutex_t g_ThreadFlagMutex;

/*! \brief Perform one-time initialization of the flag.
 *
 *  \return           void.
 */
void InitializeFlag()
{
  pthread_mutex_init(&g_ThreadFlagMutex, NULL);
  g_ThreadFlag = 0;
}

/*! \brief     Calls DoWork repeatedly while the thread flag is set;
 *             otherwise spins.
 *
 *  \param     threadArg        An argument to the thread function.
 *
 *  \return    void.
 */
void* ThreadFunction(void* threadArg)
{
  while (!0)
  {
    int flagIsSet;

    /* Protect the flag with a mutex lock.  */
    pthread_mutex_lock(&g_ThreadFlagMutex);
    flagIsSet = g_ThreadFlag;
    pthread_mutex_unlock(&g_ThreadFlagMutex);

    if (flagIsSet)
      DoWork();
    /* Else don't do anything.  Just loop again.  */
  }
  return NULL;
}

/*! \brief     Sets the value of the thread flag.
 *
 *  \param     flagValue     An exact flag value.
 *
 *  \return    void.
 */
void SetThreadFlag(int flagValue)
{
  /* Protect the flag with a mutex lock.  */
  pthread_mutex_lock(&g_ThreadFlagMutex);
  g_ThreadFlag = flagValue;
  pthread_mutex_unlock(&g_ThreadFlagMutex);
}
