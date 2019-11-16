#ifdef _MSC_VER

#include <WinSock2.h>

#elif _WIN32

#include <fcntl.h>
#include <sys/types.h>
#include <winsock2.h>
#include <unistd.h>

#else

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#endif

#include "Socket.h"

int InitializeSockets()
{
#ifdef _WIN32
    WSADATA WsaData;
    return WSAStartup(MAKEWORD(2, 2), &WsaData);
#else
    return NO_ERROR;
#endif
}

int ShutdownSockets()
{
#ifdef _WIN32
    WSACleanup();
    return NO_ERROR;
#endif
    return NO_ERROR;
}

//SocketHandle SocketCreate(int domain, int type, int protocol)
//{
//    return socket(domain, type, protocol);
//}

int CloseSocket(SocketHandle sockfd)
{
#ifdef _WIN32
    return closesocket(sockfd);
#else
    return close(sockfd);
#endif
}

//int ConnectSocket(SocketHandle sockfd,
//                  const struct sockaddr* addr, int addrlen)
//{
//    return connect(sockfd, addr, addrlen);
//}
//
//int BindSocket(SocketHandle sockfd, const struct sockaddr* addr, int addrlen)
//{
//    return bind(sockfd, addr, addrlen);
//}
//
//int ListenSocket(SocketHandle sockfd, int backlog)
//{
//    return listen(sockfd, backlog);
//}
//
//int AcceptSocket(SocketHandle socket, struct sockaddr* addr, int* addrlen)
//{
//    return accept(socket, addr, addrlen);
//}
//
//int RecvSocket(SocketHandle fd, void* pBuf, int count, int flags)
//{
//    return recv(fd, pBuf, count, flags);
//}
//
//int SendSocket(SocketHandle fd, void* pBuf, int count, int flags)
//{
//    return send(fd, pBuf, count, flags);
//}
