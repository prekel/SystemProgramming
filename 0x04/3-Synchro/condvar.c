/*! \file    condvar.c
 *  \brief   Condvars using to control a thread.
 *
 *  \details Thread worker controlled by condvars and mutexes.
 */

#include <pthread.h>

extern void DoWork();

int g_ThreadFlag;
pthread_mutex_t g_ThreadFlagMutex;
pthread_cond_t g_ThreadFlagCondVar;

/*! \brief Perform one-time initialization of the flags.
 *
 *  \return           void.
 */
void InitializeFlag()
{
  /* Initialize the mutex and condition variable.  */
  pthread_mutex_init(&g_ThreadFlagMutex, NULL);
  pthread_cond_init(&g_ThreadFlagCondVar, NULL);

  /* Initialize the flag value.  */
  g_ThreadFlag = 0;
}

/*! \brief     Calls DoWork repeatedly while the thread flag is set;
 *             blocks if the flag is clear.
 *
 *  \param     threadArg        An argument to the thread function.
 *
 *  \return    void.
 */
void* ThreadFunction(void* threadArg)
{
  /* Loop infinitely.  */
  while (!0)
  {
    /* Lock the mutex before accessing the flag value.  */
    pthread_mutex_lock(&g_ThreadFlagMutex);

    while (0 == g_ThreadFlag)

      /* The flag is clear.  Wait for a signal on the condition
	 variable, indicating the flag value has changed.  When the
	 signal arrives and this thread unblocks, loop and check the
	 flag again.  */
      pthread_cond_wait(&g_ThreadFlagCondVar, &g_ThreadFlagMutex);

    /* When we've gotten here, we know the flag must be set.  Unlock
       the mutex.  */
    pthread_mutex_unlock(&g_ThreadFlagMutex);

    /* Do some work.  */
    DoWork ();
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
  /* Lock the mutex before accessing the flag value.  */
  pthread_mutex_lock(&g_ThreadFlagMutex);

  /* Set the flag value, and then signal in case thread_function is
     blocked, waiting for the flag to become set.  However,
     thread_function can't actually check the flag until the mutex is
     unlocked.  */
  g_ThreadFlag = flagValue;
  pthread_cond_signal(&g_ThreadFlagCondVar);

  /* Unlock the mutex.  */
  pthread_mutex_unlock(&g_ThreadFlagMutex);
}
