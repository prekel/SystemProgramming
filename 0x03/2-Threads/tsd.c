/*! \file    tsd.c
 *  \brief   Thread logging
 *
 *  \details Create a log file for each thread
 *           using thread-specific data.
 */

#include <malloc.h>
#include <pthread.h>
#include <stdio.h>

/*! The key used to assocate a log file pointer with each thread. */
static pthread_key_t g_ThreadLogKey;

/*! \brief Write message to log file
 *
 *  \details Write message to the log file for the current thread.
 *
 *  \param   message     char buffer to log.
 *
 *  \return  void
 */
void WriteToThreadLog(const char* message)
{
  FILE* threadLog = (FILE*) pthread_getspecific(g_ThreadLogKey);
  fprintf(threadLog, "%s\n", message);
}

/*! \brief Close the log.
 *
 *  \details Close the log file pointer.
 *
 *  \return void
 */
void CloseThreadLog(void* threadLog)
{
  fclose((FILE*) threadLog);
}

/*! \brief Thread function.
 *
 *  \param threadArg  An argument to the thread function.
 *
 *  \return           NULL.
 *
 *  \par      Side effect: changes g_ThreadLogKey
 */
void* ThreadFunction(void* threadArg)
{
  char threadLogFilename[20];
  FILE* threadLog;

  /* Generate the filename for this thread's log file.  */
  sprintf(threadLogFilename, "thread%d.log", (int) pthread_self());

  /* Open the log file.  */
  threadLog = fopen(threadLogFilename, "w");

  /* Store the file pointer in thread-specific data under g_threadLogKey.  */
  pthread_setspecific(g_ThreadLogKey, threadLog);

  WriteToThreadLog("Thread starting.");

  /* Do work here... */
  return NULL;
}

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main()
{
  int i;
  pthread_t threads[5];

  /* Create a key to associate thread log file pointers in
     thread-specific data.  Use CloseThreadLog to clean up the file
     pointers.  */
  pthread_key_create(&g_ThreadLogKey, CloseThreadLog);

  /* Create threads to do the work.  */
  for (i = 0; i < 5; ++i)
    pthread_create(&(threads[i]), NULL, ThreadFunction, NULL);

  /* Wait for all threads to finish.  */
  for (i = 0; i < 5; ++i)
    pthread_join(threads[i], NULL);

  return 0;
}
