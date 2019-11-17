#include <errno.h>

#include "Socket.h"
#include "LastErrorMessage.h"

#ifdef WSAECONNREFUSED
#define MY_ECONNREFUSED WSAECONNREFUSED
#else
#define MY_ECONNREFUSED ECONNREFUSED
#endif
#define MY_ECONNREFUSED_MESSAGE "В соеденении отказано.\n"

#ifdef WSAETIMEDOUT
#define MY_ETIMEDOUT WSAETIMEDOUT
#else
#define MY_ETIMEDOUT ETIMEDOUT
#endif
#define MY_ETIMEDOUT_MESSAGE "Tайм-аут соеденения.\n"

#define UNKNOWN_MESSAGE "Неизвестная ошибка\n"

char* LastErrorMessage()
{
    int error;
#ifdef _WIN32
    error = WSAGetLastError();
#else
    error = errno;
#endif
    return ErrorMessage(error);
}

char* ErrorMessage(int error)
{
    switch (error)
    {
    case MY_ECONNREFUSED:
        return MY_ECONNREFUSED_MESSAGE;
    case MY_ETIMEDOUT:
        return MY_ETIMEDOUT_MESSAGE;
    default:
        return UNKNOWN_MESSAGE;
    }
}
