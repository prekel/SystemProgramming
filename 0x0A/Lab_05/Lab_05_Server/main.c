#include <stdio.h>

#include "Matrix.h"
#include "Socket.h"
#include "Request.h"

int main(int argc, char** argv)
{
    InitializeSockets();

    SocketHandle sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    int port = 12345;
    struct sockaddr_in name;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    name.sin_family = AF_INET;
    name.sin_port = htons((u_short) port);
    name.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (const struct sockaddr*) &name, sizeof(name)) == -1)
    {
        closesocket(sock);
        return 1;
    }

    if (listen(sock, 5) == -1)
    {
        closesocket(sock);
        return 1;
    }

    struct sockaddr_in clientName;
    int clientNameLength = sizeof(clientName);
    SocketHandle clientSocketFileDescriptor;

    clientSocketFileDescriptor = accept(sock,
                                        (struct sockaddr*) &clientName,
                                        &clientNameLength);

    Request request;
    ReceiveRequest(clientSocketFileDescriptor, &request);

    Matrix* m = CreateEmptyMatrix(ntohl(request.NetCount),
                                  ntohl(request.NetCount));

    ReceiveMatrix(clientSocketFileDescriptor, &request, m);

    closesocket(clientSocketFileDescriptor);

    //shutdown(sock, SHUT_WR);

    closesocket(sock);

    ShutdownSockets();

    for (int i = 0; i < m->FirstCount; i++)
    {
        for (int j = 0; j < m->SecondCount; j++)
        {
            printf("%d ", m->pData[i][j]);
        }
        printf("\n");
    }

    return 0;
}
