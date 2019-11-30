/// \file
/// \brief Реализация функций из LastErrorMessage.h
/// \details Реализация функций из LastErrorMessage.h.

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

#ifdef _WIN32
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  error,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  message,
                  MESSAGE_BUF_SIZE,
                  NULL);
#else
    strerror_r(error, message, MESSAGE_BUF_SIZE);
#endif

    fprintf(stderr,
            message[strlen(message) - 1] == '\n' ? "%s" : "%s\n",
            message);
}
