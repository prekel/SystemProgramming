#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_strings(char const* in)
{
  char* cmd;
  int len = strlen("strings: ") + strlen(in) + 1;
  cmd = malloc(len);
  snprintf(cmd, len, "strings %s", in);
  if (0 != system(cmd))
    fprintf(stderr, "Smth wrong %s.\n", cmd);
  free(cmd);
  free(cmd);
}

int main(int argc, char* argv[])
{
  get_strings(argv[0]);
}

