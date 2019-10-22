#include <stdio.h>
#include <stdlib.h>

int main()
{
  int* i = (int *) malloc(sizeof (int));
  *i = 10;
  free(i);
  printf("%d\n", *i);
  return 0;
}
