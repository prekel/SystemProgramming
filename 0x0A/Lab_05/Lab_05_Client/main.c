#include "Matrix.h"
#include "Socket.h"
#include "Request.h"

int main(int argc, char** argv)
{
    int port = 12345;
    char* loopback = "127.0.0.1";

    Matrix* m = CreateEmptyMatrix(3, 3);
    m->pData[0][0] = 1;
    m->pData[0][1] = 2;
    m->pData[0][2] = 3;
    m->pData[1][0] = 4;
    m->pData[1][1] = 5;
    m->pData[1][2] = 6;
    m->pData[2][0] = 7;
    m->pData[2][1] = 8;
    m->pData[2][2] = 9;

    Request request;
    FillRequest(&request, m, 1, 1);

    InitializeSockets();

    SocketHandle sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in name;

    name.sin_family = AF_INET;
    name.sin_addr.s_addr = inet_addr(loopback);

    name.sin_port = htons((uint16_t) port);

    if (connect(sock, (struct sockaddr*) &name, sizeof(name)) == -1)
    {
        closesocket(sock);
        return 1;
    }

    SendRequest(sock, &request);

    SendMatrix(sock, &request, m);

    //shutdown(sock, SHUT_WR);

    closesocket(sock);

    ShutdownSockets();

    return 0;
}
