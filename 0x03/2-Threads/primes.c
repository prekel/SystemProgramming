/*! \file    primes.c
 *  \brief   Count Nth prime number.
 *
 *  \details Brute-force computing successive prime numbers.
 */

#include <pthread.h>
#include <stdio.h>

/*! \brief Compute prime numbers.
 *
 *  \details Compute Nth prime number (very inefficiently), as given by ARG.
 *
 *  \param arg        A number of prime number to compute.
 *  \return           An Nth prime number or NULL, if cannot compute.
 */
void* ComputePrime (void* arg)
{
  int candidate = 2;
  int n = *((int*) arg);

  while (!0) {
    int factor;
    int isPrime = 1;

    /* Test primality by successive division.  */
    for (factor = 2; factor < candidate; ++factor)
      if (candidate % factor == 0) {
        isPrime = 0;
        break;
      }

    /* Is this the prime number we're looking for?  */
    if (isPrime) {
      if (--n == 0)

        /* Return the desired prime number as the thread return value.  */
        return (void*) candidate;
    }
    ++candidate;
  }
  return NULL;
}

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */

int main()
{
  pthread_t thread;
  int whichPrime = 500;
  int prime;

  /* Start the computing thread, up to the 500th prime number.  */
  pthread_create(&thread, NULL, &ComputePrime, &whichPrime);

  /* Do some other work here...  */
  /* Wait for the prime number thread to complete, and get the result.  */
  pthread_join(thread, (void*) &prime);

  /* Print the largest prime it computed.  */
  printf("The %dth prime number is %d.\n", whichPrime, prime);
  return 0;
}
