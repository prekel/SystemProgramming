/*! \file    pipe-3.c
 *  \brief   Pipe demonstration.
 *
 *  \details Interprocess communication via pipe, using popen() and pclose().
 *           Parent process is writer, and child proccess ("sort") is reader.
 */
#include <stdio.h>
#include <unistd.h>

/*! \brief Main function
 *  \return pclose() exit code
 */
int main()
{
  FILE* stream = popen("sort", "w");
  fprintf(stream, "3. I don't know what it is that I like about you, but I like it a lot.\n");
  fprintf(stream, "1. Hey, girl, stop what you're doin'!\n");
  fprintf(stream, "5. Communication Breakdown, It's always the same,\n");
  fprintf(stream, "2. Hey, girl, you'll drive me to ruin.\n");
  fprintf(stream, "6. I'm having a nervous breakdown, Drive me insane!\n");
  fprintf(stream, "4. Won't let me hold you, Let me feel your lovin' charms.\n");

  return pclose(stream);
}
