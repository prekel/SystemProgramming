#ifndef SOCKET_H
#define SOCKET_H

#ifdef _MSC_VER

#include <WinSock2.h>

#elif _WIN32

#include <winsock2.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#else

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#endif


#ifndef NO_ERROR
#define NO_ERROR 0
#endif

#ifdef SD_RECEIVE
#define SHUT_RD SD_RECEIVE
#endif
#ifdef SD_SEND
#define SHUT_WR SD_SEND
#endif
#ifdef SD_BOTH
#define SHUT_RDWR SD_BOTH
#endif

#ifdef _WIN32
typedef SOCKET SocketHandle;
#else
typedef int SocketHandle;
#endif


#ifndef _WIN32
#define closesocket(sock) close(sock)
#endif

int InitializeSockets();

int ShutdownSockets();

#endif //SOCKET_H
