/*! \file    socket-internet.c
 *  \brief   Internet sockets demonstration.
 *
 *  \details Interprocess communication via intternet sockets.
 *           Connect to the web server given by hostname and 80th port.
 *           Retrieve the server's home page, and print it out.
 */
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

/* Print the contents of the home page for the server's socket.
   Return an indication of success.  */

/*! \brief Print webserver's homepage.
 *
 *  \details Print the contents of the home page for the server's socket.
 *           Return indication of success.
 *  \param  socketFileDescriptor     Target socket descriptor
 */
void GetHomePage(int socketFileDescriptor)
{
  char buffer[10000];
  ssize_t numberCharactersRead;

  /* Send the HTTP GET command for the home page.  */
  sprintf(buffer, "GET /\n");
  write(socketFileDescriptor, buffer, strlen(buffer));

  /* Read from the socket.  read may not return all the data at one
     time, so keep trying until we run out.  */
  while (!0)
  {
    numberCharactersRead = read(socketFileDescriptor, buffer, 10000);
    if (numberCharactersRead == 0)
      return;

    /* Write the data to standard output.  */
    fwrite(buffer, sizeof (char), numberCharactersRead, stdout);
  }
}

/*! \brief Main function
 *  \param argc  Number of command line arguments
 *  \param argv  An array of command line argruments.
 *               argv[0] - the program name,
 *               argv[1] - a socket name.
 *  \return Integer 0 upon exit success,
 *          and nonzero otherwise.
 */
int main(int argc, char* const argv[])
{
  int socketFileDescriptor;
  struct sockaddr_in name;
  struct hostent* hostinfo;

  if (argc < 2)
  {
    fprintf(stderr, "Too few parameters.\n");
    return EXIT_FAILURE;
  }

  /* Create the socket.  */
  socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

  /* Store the server's name in the socket address.  */
  name.sin_family = AF_INET;

  /* Convert from strings to numbers.  */
  hostinfo = gethostbyname(argv[1]);
  if (hostinfo == NULL)
    return 1;
  else
    name.sin_addr = *((struct in_addr *) hostinfo->h_addr);

  /* Web servers use port 80.  */
  name.sin_port = htons(80);

  /* Connect to the web server  */
  if (connect(socketFileDescriptor, (const struct sockaddr *)&name
              , sizeof (struct sockaddr_in)) == -1
             )
  {
    perror("connect");
    return !0;
  }
  /* Retrieve the server's home page.  */
  GetHomePage(socketFileDescriptor);

  return 0;
}
