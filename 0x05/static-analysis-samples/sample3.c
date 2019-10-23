#include <stdio.h>

int main()
{
  int* fp = malloc(sizeof (int));
  free(fp);
  free(fp);
  return 0;
}
