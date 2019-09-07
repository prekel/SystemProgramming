/*! \file    assert_demo.c
 *  \brief   Assert macro demo.
 *
 *  \details Assert macro demonstration code.
 */
#include <assert.h>

/*! \brief Main function
 *  \return Integer 0 upon exit success
 */
int main()
{
  int a = 5;
  assert(a < 0);

  int b = -5;
  assert(b < 0);
  return 0;
}
