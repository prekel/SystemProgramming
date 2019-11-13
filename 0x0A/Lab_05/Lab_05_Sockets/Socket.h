#ifndef SOCKET_H
#define SOCKET_H

#ifdef _MSC_VER

#include <WinSock2.h>

#elif _WIN32

#include <sys/types.h>

#else

#include <sys/types.h>

#endif

#ifndef NO_ERROR
#define NO_ERROR 0
#endif

#ifdef _WIN32
typedef SOCKET SocketHandle;
#else
typedef int SocketHandle;
#endif

int InitializeSockets();

int ShutdownSockets();

SocketHandle SocketCreate(int domain, int type, int protocol);

int CloseSocket(SocketHandle sockfd);

int
ConnectSocket(SocketHandle sockfd, const struct sockaddr* addr, int addrlen);

int BindSocket(SocketHandle sockfd, const struct sockaddr* addr, int addrlen);

int ListenSocket(SocketHandle sockfd, int backlog);

int AcceptSocket(SocketHandle socket, struct sockaddr* addr, int* addrlen);

int RecvSocket(SocketHandle fd, void* pBuf, int count, int flags);

int SendSocket(SocketHandle fd, void* pBuf, int count, int flags);

#endif //SOCKET_H
