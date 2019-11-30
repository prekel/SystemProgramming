/*! \file    sem_all_deall.c
 *  \brief   SystemV semaphores demonstration.
 *
 *  \details Interprocess communication via semaphores:
 *           allocations and deallocations.
 */
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

/* We must define union semun ourselves.  */
/*! \union semun */
union semun
{
  int val;
  struct semid_ds* buf;
  unsigned short int* array;
  struct seminfo* __buf;
};

/*! \brief Obtain semaphore ID.
 *
 *  \details Obtain a binary semaphore's ID, allocating if necessary.
 *
 *  \param key        Semaphore group key
 *  \param semFlags   Semaphore permission flags
 *
 *  \return           Semaphore group ID
 */
int BinarySemaphoreAllocation(key_t key, int semFlags)
{
  return semget(key, 1, semFlags);
}

/*! \brief Deallocate semaphore.
 *
 *  \details         Deallocate a binary semaphore.
 *                   All users must have finished their use.
 *
 *  \param semId      Semaphore group ID
 *
 *  \return           -1, on failure with errno indication error,
 *                    nonnegative value, otherwise.
 */

int BinarySemaphoreDeallocate(int semId)
{
  union semun ignoredArgument;
  return semctl(semId, 1, IPC_RMID, ignoredArgument);
}
