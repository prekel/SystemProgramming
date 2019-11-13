/*! \file    sem_pv.c
 *  \brief   SystemV semaphores demonstration.
 *
 *  \details Interprocess communication via semaphores:
 *           operations via semop system call.
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/*! \brief Waiting on semaphore.
 *
 *  \details Wait on a binary semaphore.
 *           Block until the semaphore value is positive,
 *           then decrement it by one.
 *
 *  \param semId      Semaphore group ID
 *
 *  \return           -1, on failure with errno indication error,
 *                    0, otherwise.
 */
int BinarySemaphoreWait(int semId)
{
  struct sembuf operations[1];

  /* Use the first (and only) semaphore.  */
  operations[0].sem_num = 0;

  /* Decrement by 1.  */
  operations[0].sem_op = -1;

  /* Permit undo'ing.  */
  operations[0].sem_flg = SEM_UNDO;
  
  return semop(semid, operations, 1);
}

/*! \brief Post to a semaphore.
 *
 *  \details Post to a binary semaphore: increment its value by one.
 *           This returns immediately.
 *
 *  \param semId      Semaphore group ID
 *
 *  \return           -1, on failure with errno indication error,
 *                    0, otherwise.
 */
int BinarySemaphorePost(int semId)
{
  struct sembuf operations[1];

  /* Use the first (and only) semaphore.  */
  operations[0].sem_num = 0;

  /* Increment by 1.  */
  operations[0].sem_op = 1;

  /* Permit undo'ing.  */
  operations[0].sem_flg = SEM_UNDO;
  
  return semop(semid, operations, 1);
}
