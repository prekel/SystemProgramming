/// \file
/// \brief Сервер
/// \details Основные функции сервера.

#ifndef SERVER_H
#define SERVER_H

#include "ServerArgs.h"
#include "Matrix.h"
#include "Request.h"

/// Основная функция сервера. Устанавливает соеденение, принимает запрос,
/// создаёт матрицу, принимает матрицу, закрывает соеденение. Срабатывает
/// assert(), если pRequest или ppMatrixA или ppMatrixB или
/// pClientAddressStr равен NULL.
///
/// \param pArgs Указатель на аргументы командной строки.
/// \param pRequest Указатель на запрос.
/// \param ppMatrixA Указатель на указатель на матрицу A. Требуется очистка
/// матрицы с помощью DestroyMatrix(*ppMatrixA).
/// \param ppMatrixB Указатель на указатель на матрицу B. Требуется очистка
/// матрицы с помощью DestroyMatrix(*ppMatrixB).
/// \param pClientAddressStr Указатель на строку, в которую будет записан
/// IP-адрес клиента. Требуется очистка с помощью free(*pClientAddressStr).
/// \param pSocketToClose Указатель на сокет который требуется закрыть после
/// работы функции.
/// \return SOCKET_ERROR (-1) в случае ошибки сокета,
/// ALLOCATION_ERROR (-9) в случае ошибки аллокации,
/// SUCCESSFUL (0) в случае успеха.
int Server(Args* pArgs, Request* pRequest, Matrix** ppMatrixA,
           Matrix** ppMatrixB, char** pClientAddressStr,
           SocketHandle* pSocketToClose);

/// Устанавливает соеденение.
///
/// \param pArgs Указатель на аргумент коммандной строки.
/// \return Сокет, готовый к приёму данных в случае успеха или
/// SOCKET_ERROR (-1) в случае ошибки сокета.
SocketHandle ServerConnect(Args* pArgs);

/// Принимает запрос.
///
/// \param sock Сокет.
/// \param pRequest Указатель на запрос.
/// \return SOCKET_ERROR (-1) в случае ошибки сокета,
/// SUCCESSFUL (0) в случае успеха.
int ServerReceiveRequest(SocketHandle sock, Request* pRequest,
                         struct sockaddr* pClientAddress,
                         socklen_t* pAddressLength);

/// Принимает матрицу.
///
/// \param sock Сокет.
/// \param pRequest Указатель на запрос.
/// \param pMatrix Указатель на матрицу.
/// \return SOCKET_ERROR (-1) в случае ошибки сокета,
/// ALLOCATION_ERROR (-9) в случае ошибки аллокации,
/// SUCCESSFUL (0) в случае успеха.
int ServerReceiveMatrix(SocketHandle sock, Request* pRequest,
                        Matrix* pMatrix);

#endif //SERVER_H
