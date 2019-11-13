/*! \file    sem_init.c
 *  \brief   SystemV semaphores demonstration.
 *
 *  \details Interprocess communication via semaphores: initialization.
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/* We must define union semun ourselves.  */
/*! \union semun */
union semun
{
  int val;
  struct semid_ds* buf;
  unsigned short int* array;
  struct seminfo *__buf;
};

/*! \brief Initialize a semaphore.
 *
 *  \details Initialize a binary semaphore with a value of one.
 *
 *  \param semId      Semaphore group ID
 *
 *  \return           -1, on failure with errno indication error,
 *                    nonnegative value, otherwise.
 */
int BinarySemaphoreInitialize(int semId)
{
  union semun argument;
  unsigned short values[1];
  values[0] = 1;
  argument.array = values;
  return semctl(semId, 0, SETALL, argument);
}
