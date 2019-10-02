/*! \file    cleanup.c
 *  \brief   Cleanup handler demo.
 *
 *  \details A code snippet and demo code for cleanup handler.
 */
#include <malloc.h>
#include <pthread.h>

/*! \brief  Allocate a temporary buffer.
 *
 *  \details Allocate a temporary buffer.
 *
 *  \param   size     Buffer size.
 *
 *  \return  A pointer to memory area or NULL.
 */
void* AllocateBuffer(size_t size)
{
  return malloc(size);
}

/*! \brief  Deallocate a temporary buffer.
 *
 *  \details Deallocate a temporary buffer.
 *
 *  \param   buffer     Pointer to buffer allocation in memory.
 *
 *  \return  void.
 */
void DeallocateBuffer(void* buffer)
{
  free (buffer);
}

/*! \brief  Demo code.
 *
 *  \details Demo code for allocation and cleanup.
 *
 *  \return  void.
 */
void DoSomeWork()
{
  /* Allocate a temporary buffer.  */
  void* tempBuffer = AllocateBuffer(1024);

  /* Register a cleanup handler for this buffer, to deallocate it in
     case the thread exits or is cancelled.  */
  pthread_cleanup_push(DeallocateBuffer, tempBuffer);

  /* Do some work here that might call pthread_exit or might be
     cancelled...  */

  /* Unregister the cleanup handler.  Since we pass a non-zero value,
     this actually performs the cleanup by calling
     DeallocateBuffer.  */
  pthread_cleanup_pop(1);
}
