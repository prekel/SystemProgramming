/*! \file    socket-server.c
 *  \brief   Sockets demonstration.
 *
 *  \details Interprocess communication via local sockets.
 *           Read messages and print it out until client sent "adios amigo".
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

/*! \brief Read text from socket and print it.
 *
 *  \details Read text from the socket and print it out.
 *           Continue until the socket closes.
 *  \param  clientSocket      Text message
 *  \return non-zero, if the client sent a "adios amigo" message,
 *          zero otherwise.
 */
int server(int clientSocket)
{
  while (!0)
  {
    int length;
    char* text;

    /* First, read the length of the text message from the socket.  If
       read returns zero, the client closed the connection.  */
    if (read(clientSocket, &length, sizeof (length)) == 0)
      return 0;

    /* Allocate a buffer to hold the text.  */
    text = (char*) malloc(length);

    /* Read the text itself, and print it.  */
    read(clientSocket, text, length);
    printf("%s\n", text);

    /* If the client sent the message "adios amigo", we're all done.  */
    if (0 == strcmp(text, "adios amigo"))
    {
      /* Free the buffer.  */
      free(text);
      return !0;
    }
    /* Free the buffer.  */
    free(text);
  }
  return 0;
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
  if (argc < 2)
  {
    fprintf(stderr, "Too few parameters.\n");
    return EXIT_FAILURE;
  }
  const char* const socketName = argv[1];
  int socketFileDescriptor;
  struct sockaddr_un name;
  int clientSentQuitMessage;

  /* Create the socket.  */
  socketFileDescriptor = socket(AF_LOCAL, SOCK_STREAM, 0);

  /* Indicate this is a server.  */
  name.sun_family = AF_LOCAL;
  strcpy (name.sun_path, socketName);
  bind(socketFileDescriptor, (const struct sockaddr *)&name, SUN_LEN(&name));

  /* Listen for connections.  */
  listen(socketFileDescriptor, 4);

  /* Repeatedly accept connections, spinning off one server() to deal
     with each client.  Continue until a client sends
     a "adios amigo" message.  */
  do
  {
    struct sockaddr_un clientName;
    socklen_t clientNameLength;
    int clientSocketFileDescriptor;

    /* Accept a connection.  */
    clientSocketFileDescriptor = accept(socketFileDescriptor
                                        , (__SOCKADDR_ARG)&clientName
                                        , &clientNameLength
                                       );
    /* Handle the connection.  */
    clientSentQuitMessage = server(clientSocketFileDescriptor);
    /* Close our end of the connection.  */
    close(clientSocketFileDescriptor);
  } while (!clientSentQuitMessage);

  /* Remove the socket file.  */
  close(socketFileDescriptor);
  unlink(socketName);

  return 0;
}
