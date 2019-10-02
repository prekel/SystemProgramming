/*! \file    job-queue1.c
 *  \brief   Processing queued jobs.
 *
 *  \details A code snippet for processing queued jobs.
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

/*! \brief Process queued jobs until the queue is empty.
 *
 *  \param arg        An argument to the thread function.
 *  \return           NULL.
 */
void* ThreadFunction(void* arg)
{
  while (g_JobQueue != NULL)
  {
    /* Get the next available job.  */
    struct job* nextJob = g_JobQueue;

    /* Remove this job from the list.  */
    g_JobQueue = g_JobQueue->next;

    /* Carry out the work.  */
    ProcessJob(nextJob);

    /* Clean up.  */
    free(nextJob);
  }
  return NULL;
}
