/// \file
/// \brief Сокеты
/// \details Заголовочные файлы, константы, макросы, типы, функции для
/// совместимости BSD-сокетов и WinSock.

#ifndef SOCKET_H
#define SOCKET_H

#ifdef _MSC_VER
#include <WinSock2.h>
#include <Windows.h>
#elif _WIN32
#include <winsock2.h>
#include <windows.h>
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

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

/// Если f == SOCKET_ERROR, то вызывающая функция
/// возвращает SOCKET_ERROR.
///
/// \param f Проверяемое целое число или выражение, возвращающее целое число.
#define RETURN_IF_SOCKET_ERROR(f) do { \
    int tmp = (f); \
    if (tmp == SOCKET_ERROR) \
    { \
        return SOCKET_ERROR; \
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

#ifndef __socklen_t_defined
#define socklen_t int
#endif

/// Инициализирует сокеты. На Linux ничего не делает.
///
/// \return NO_ERROR (0) в случае успеха или Linux, результат
/// выполнения WSAStartup() на Windows в случае неудачи.
int InitializeSockets();

/// Завершает использование сокетов. На Linux ничего не делает. На Windows
/// вызывает WSACleanup().
void ShutdownSockets();

#endif //SOCKET_H
