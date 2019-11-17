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

void ShutdownSockets()
{
#ifdef _WIN32
    WSACleanup();
#endif
}
