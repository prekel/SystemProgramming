#include <stdio.h>
#include <stdlib.h>

int main()
{
  int* a = (int*)NULL;
  int f = 1 / *a;
  
  printf("%d\n", f);
  return 0;
}
