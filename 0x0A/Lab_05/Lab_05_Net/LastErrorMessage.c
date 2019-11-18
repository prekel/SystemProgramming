#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "Socket.h"
#include "LastErrorMessage.h"

int LastError()
{
#ifdef _WIN32
    return WSAGetLastError();
#else
    return errno;
#endif
}

void PrintLastErrorMessage()
{
    PrintErrorMessage(LastError());
}

#define MESSAGE_BUF_SIZE 256

void PrintErrorMessage(int error)
{
    char message[MESSAGE_BUF_SIZE] = "";

    //message[0] = '\0';

#ifdef _WIN32
    FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL,
                   error,
                   MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
                   message,
                   MESSAGE_BUF_SIZE,
                   NULL);
#else
    strerror_r(error, message, MESSAGE_BUF_SIZE);
#endif

    fprintf(stderr, "%s\n", message);
}
