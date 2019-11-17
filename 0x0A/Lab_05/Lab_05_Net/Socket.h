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
#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

#define RETURN_IF_SOCKET_ERROR(f) do { \
    int tmp = (f); \
    if (tmp == SOCKET_ERROR) \
    { \
        return tmp; \
    } \
} while (0)

#ifdef _WIN32
typedef SOCKET SocketHandle;
#else
typedef int SocketHandle;
#endif

#ifndef _WIN32
#define closesocket(sock) close(sock)
#endif

int InitializeSockets();

void ShutdownSockets();

#endif //SOCKET_H
