/*! \file    critical-section.c
 *  \brief   Process critical data within threads.
 *
 *  \details Demo to the processing critical data within threads.
 */

#include <pthread.h>
#include <stdio.h>
#include <string.h>

/*! An array of balances in accounts, indexed by account number. */
float* g_AccountBalances;

/* Transfer DOLLARS from account FROMACCOUNT to account TOACCOUNT.  Return
   0 if the transaction succeeded, or 1 if the balance FROM_ACCT is
   too small.  */

/*! \brief Transfer "dollars" from account "fromAccount" to account toAccount.
 *
 *  \param fromAccount A source account.
 *  \param toAccount   A target account.
 *  \param dollars     Money to transfer.
 *  \return            0, upon success;
 *                     1, upon error (insuffcient money in fromAccount).
 */

int ProcessTransaction(int fromAccount, int toAccount, float dollars)
{
  int oldCancelState;

  /* Check the balance in FROM_ACCT.  */
  if (g_AccountBalances[fromAccount] < dollars)
    return 1;

  /* Begin critical section.  */
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldCancelState);

  /* Move the money.  */
  g_AccountBalances[toAccount] += dollars;
  g_AccountBalances[fromAccount] -= dollars;

  /* End critical section.  */
  pthread_setcancelstate(oldCancelState, NULL);

  return 0;
}
