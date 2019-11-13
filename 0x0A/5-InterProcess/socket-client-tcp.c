/*! \file    socket-client-tcp.c
 *  \brief   Sockets demonstration.
 *
 *  \details Interprocess communication via TCP sockets.
 *           Write message to the socket.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
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
  int length = strlen(text) + 1;
  send(socketFileDescriptor, &length, sizeof (length), 0);

  /* Write the string.  */
  send(socketFileDescriptor, text, length, 0);
}

/*! \brief Main function
 *  \param argc  Number of command line arguments
 *  \param argv  An array of command line argruments.
 *               argv[0] - the program name,
 *               argv[1] - a socket IP-address.
 *               argv[2] - a socket port number.
 *  \return Integer 0 upon exit success,
 *          or EXIT_FAILURE otherwise.
 */
int main(int argc, const char* argv[])
{
  if (argc != 3)
  {
    fprintf(stderr, "Socketname and port number expected.\n");
    return EXIT_FAILURE;
  }

  int socketFileDescriptor;
  int portNumber = atoi(argv[2]);
  
  struct sockaddr_in name;
  memset((char *) &name, 0, sizeof (name));

  /* Store the server's name in the socket address.  */
  name.sin_family = AF_INET;
  name.sin_addr.s_addr = inet_addr(argv[1]);

  if (INADDR_NONE == name.sin_addr.s_addr)
  {
    perror("inet_addr");
    exit(1);
  }
  name.sin_port = htons((u_short)portNumber);

  /* Create the socket.  */
  socketFileDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (0 > socketFileDescriptor)
    perror("socket");
  int i = 1;
  setsockopt(socketFileDescriptor, SOL_SOCKET, SO_REUSEADDR,
             (const char *)&i, sizeof (i)
            );

  /* Connect the socket.  */
  if (0 > connect(socketFileDescriptor,
                  (struct sockaddr *) &name,
                  (socklen_t) sizeof (name))
                 )
  {
    perror("connect");
    exit(1);
  }

  /* Write the text to the socket.  */
  char message[256];
  do
  {
    message[0] = '\0';
    printf("Please, enter a string to send to server.\n");
    printf("To quit enter \"adios amigo\"\n");
    fgets(message, 256, stdin);
    message[strlen(message) - 1] = 0;
    WriteText(socketFileDescriptor, message);
    if (0 == strcmp(message, "adios amigo"))
      break;
  } while (!0);

  /* Disconnect and remove the socket. */
  shutdown(socketFileDescriptor, SHUT_WR);
  close(socketFileDescriptor);
  return 0;
}
