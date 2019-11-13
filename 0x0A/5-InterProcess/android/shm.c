/*! \file    shm.c
 *  \brief   Shared memory demonstration.
 *
 *  \details Interprocess communication via shared memory.
 */
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main()
{
  int segmentId;
  char* sharedMemory;
  struct shmid_ds shmBuffer;
  int segmentSize;
  const int sharedSegmentSize = 0x6400;

  /* Allocate a shared memory segment.  */
  segmentId = shmget(IPC_PRIVATE, sharedSegmentSize,
                      IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

  /* Attach the shared memory segment.  */
  sharedMemory = (char*) shmat(segmentId, 0, 0);
  printf("shared memory attached at address %p\n", sharedMemory);

  /* Determine the segment's size.  */
  shmctl(segmentId, IPC_STAT, &shmBuffer);
  segmentSize = shmBuffer.shm_segsz;
  printf("segment size: %d\n", segmentSize);

  /* Write a string to the shared memory segment.  */
  sprintf(sharedMemory, "Hello, world.");

  /* Deatch the shared memory segment.  */
  shmdt(sharedMemory);

  /* Reattach the shared memory segment, at a different address.  */
  sharedMemory = (char*) shmat(segmentId, (void*) 0x5000000, 0);
  printf("shared memory reattached at address %p\n", sharedMemory);

  /* Print out the string from shared memory.  */
  printf("%s\n", sharedMemory);

  /* Detach the shared memory segment.  */
  shmdt(sharedMemory);

  /* Deallocate the shared memory segment.  */
  shmctl(segmentId, IPC_RMID, 0);

  return 0;
}
