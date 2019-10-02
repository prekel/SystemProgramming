/*! \file    pthread-2.c
 *  \brief   Print charaters by two threads.
 *
 *  \details Printing characters to stderr.
 *           Second and third threads to be created by first (main) thread.
 *
 *  \bug     Program may finish before the end of additional threads.
 */

#include <pthread.h>
#include <stdio.h>

/*! \struct TCharPrintParams
 *  \brief  Parameters to print_function.
*/
struct TCharPrintParams
{
  /*! The character to print.  */
  char character;

  /*! The number of times to print it.  */
  int count;
};

/*! \brief Prints a number of characters to stderr
 *
 *  \details Prints a number of characters to stderr, as given by PARAMETERS.
 *           
 *  \param parameters A pointer to a struct TCharPrintParams.
 *  \return NULL-pointer
 */

void* PrintChars(void* parameters)
{
  /* Cast the cookie pointer to the right type.  */
  struct TCharPrintParams* p = (struct TCharPrintParams *) parameters;
  int i;

  for (i = 0; i < p->count; ++i)
    fputc(p->character, stderr);
  return NULL;
}

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */

int main()
{
  pthread_t thread1Id;
  pthread_t thread2Id;
  struct TCharPrintParams thread1Args;
  struct TCharPrintParams thread2Args;

  /* Create a new thread to print 300 y's.  */
  thread1Args.character = 'y';
  thread1Args.count = 300;
  pthread_create(&thread1Id, NULL, &PrintChars, &thread1Args);

  /* Create a new thread to print 200 e's.  */
  thread2Args.character = 'e';
  thread2Args.count = 200;
  pthread_create(&thread2Id, NULL, &PrintChars, &thread2Args);

  return 0;
}
