/*! \file    job-queue2.c
 *  \brief   Processing queued jobs.
 *
 *  \details A code snippet for processing queued jobs and demo for mutexes.
 */
#include <malloc.h>
#include <pthread.h>

struct job
{
  /* Link field for linked list.  */
  struct job* next; 

  /* Other fields describing work to be done... */
};

/* A linked list of pending jobs.  */
struct job* g_JobQueue;

extern void ProcessJob(struct job*);

/* A mutex protecting job_queue.  */
pthread_mutex_t g_JobQueueMutex = PTHREAD_MUTEX_INITIALIZER;

/*! \brief Process queued jobs until the queue is empty.
 *
 *  \param arg        An argument to the thread function.
 *  \return           NULL.
 */
void* ThreadFunction(void* arg)
{
  while (!0)
  {
    struct job* nextJob;

    /* Lock the mutex on the job queue.  */
    pthread_mutex_lock(&g_JobQueueMutex);

    /* Now it's safe to check if the queue is empty.  */
    if (g_JobQueue == NULL)
      nextJob = NULL;
    else
    {
      /* Get the next available job.  */
      nextJob = g_JobQueue;

      /* Remove this job from the list.  */
      g_JobQueue = g_JobQueue->next;
    }
    /* Unlock the mutex on the job queue, since we're done with the
       queue for now.  */
    pthread_mutex_unlock(&g_JobQueueMutex);

    /* Was the queue empty?  If so, end the thread.  */
    if (nextJob == NULL)
      break;

    /* Carry out the work.  */
    ProcessJob(nextJob);

    /* Clean up.  */
    free(nextJob);
  }
  return NULL;
}

