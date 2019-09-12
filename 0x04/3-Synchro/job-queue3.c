/*! \file    job-queue3.c
 *  \brief   Processing queued jobs.
 *
 *  \details A code snippet for processing queued jobs
 *           and demo for mutexes and thread semaphores.
 */
#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>

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

/* A semaphore counting the number of jobs in the queue.  */
sem_t g_JobQueueCount;

/*! \brief Perform one-time initialization of the job queue.
 *
 *  \return           void.
 */
void InitializeJobQueue()
{
  /* The queue is initially empty.  */
  g_JobQueue = NULL;

  /* Initialize the semaphore which counts jobs in the queue.  Its
     initial value should be zero.  */
  sem_init(&g_JobQueueCount, 0, 0);
}

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

    /* Wait on the job queue semaphore.  If its value is positive,
       indicating that the queue is not empty, decrement the count by
       one.  If the queue is empty, block until a new job is enqueued.  */
    sem_wait(&g_JobQueueCount);

    /* Lock the mutex on the job queue.  */
    pthread_mutex_lock(&g_JobQueueMutex);

    /* Because of the semaphore, we know the queue is not empty.  Get
       the next available job.  */
    nextJob = g_JobQueue;

    /* Remove this job from the list.  */
    g_JobQueue = g_JobQueue->next;

    /* Unlock the mutex on the job queue, since we're done with the
       queue for now.  */
    pthread_mutex_unlock(&g_JobQueueMutex);

    /* Carry out the work.  */
    ProcessJob(nextJob);

    /* Clean up.  */
    free(nextJob);
  }
  return NULL;
}

/*! \brief Add a new job to the front of the job queue.
 *
 *  \return           void.
 *
 *  \par              No check for memory allocation.
 */
void EnqueueJob(/* Pass job-specific data here...  */)
{
  struct job* newJob;

  /* Allocate a new job object.  */
  newJob = (struct job*) malloc (sizeof (struct job));

  /* Set the other fields of the job struct here...  */

  /* Lock the mutex on the job queue before accessing it.  */
  pthread_mutex_lock(&g_JobQueueMutex);

  /* Place the new job at the head of the queue.  */
  newJob->next = g_JobQueue;
  g_JobQueue = newJob;

  /* Post to the semaphore to indicate another job is available.  If
     threads are blocked, waiting on the semaphore, one will become
     unblocked so it can process the job.  */
  sem_post(&g_JobQueueCount);

  /* Unlock the job queue mutex.  */
  pthread_mutex_unlock(&g_JobQueueMutex);
}
