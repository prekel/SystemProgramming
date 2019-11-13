/*! \file    socket-client.c
 *  \brief   Sockets demonstration.
 *
 *  \details Interprocess communication via local sockets.
 *           Write message to the socket.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

/*! \brief Write text to a socket.
 *
 *  \details Write text to the socket given by file descriptor.
 *
 *  \param socketFileDescriptor    Target file descriptor
 *  \param text                    Text message
 */
void WriteText(int socketFileDescriptor, const char* text)
{
  /* Write the number of bytes in the string, including
     NULL-termination.  */
  int length = strlen(text)+1;
  write(socketFileDescriptor, &length, sizeof (length));

  /* Write the string.  */
  write (socketFileDescriptor, text, length);
}

/*! \brief Main function
 *  \param argc  Number of command line arguments
 *  \param argv  An array of command line argruments.
 *               argv[0] - the program name,
 *               argv[1] - a socket name.
 *  \return Integer 0 upon exit success,
 *          or EXIT_FAILURE otherwise.
 */
int main(int argc, char* const argv[])
{
  if (argc != 3)
  {
    fprintf(stderr, "Socketname and text messages expected.\n");
    return EXIT_FAILURE;
  }

  const char* const socket_name = argv[1];
  const char* const message = argv[2];
  int socketFileDescriptor;
  struct sockaddr_un name;

  /* Create the socket.  */
  socketFileDescriptor = socket(AF_LOCAL, SOCK_STREAM, 0);

  /* Store the server's name in the socket address.  */
  name.sun_family = AF_LOCAL;
  strcpy(name.sun_path, socket_name);

  /* Connect the socket.  */
  connect(socketFileDescriptor, (const struct sockaddr *)&name, SUN_LEN (&name));

  /* Write the text on the command line to the socket.  */
  WriteText(socketFileDescriptor, message);
  close(socketFileDescriptor);
  return 0;
}
