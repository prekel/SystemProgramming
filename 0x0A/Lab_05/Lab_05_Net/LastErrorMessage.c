#include <errno.h>
#include <stdio.h>

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

#define UNKNOWN_MESSAGE "Неизвестная ошибка: %d\n"


int LastError()
{
#ifdef _WIN32
    return WSAGetLastError();
#else
    return errno;
#endif
}

char* LastErrorMessage()
{
    return ErrorMessage(LastError());
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

void PrintLastErrorMessage()
{
    int error = LastError();
    PrintErrorMessage(error);
}

void PrintErrorMessage(int error)
{
    char* message = ErrorMessage(error);
    if (error == NO_ERROR)
    {
        return;
    }
    else if (message == UNKNOWN_MESSAGE)
    {
        fprintf(stderr, UNKNOWN_MESSAGE, error);
    }
    else
    {
        fprintf(stderr, "%s", message);
    }
}
