/// \file
/// \brief Сервер
/// \details Основные функции сервера.

#ifndef SERVER_H
#define SERVER_H

#include "Args.h"
#include "Matrix.h"
#include "Request.h"

/// Основная функция сервера. Устанавливает соеденение, принимает запрос,
/// создаёт матрицу, принимает матрицу, закрывает соеденение.
/// Требуется очистка матрицы с помощью DestroyMatrix().
///
/// \param pArgs Указатель на аргументы командной строки.
/// \param pRequest Указатель на запрос.
/// \param ppMatrixA Указатель на указатель на матрицу A.
/// \param ppMatrixA Указатель на указатель на матрицу B.
/// \param pSocketToClose1 Указатель на сокет который требуется закрыть после
/// работы функции.
/// \param pSocketToClose1 Указатель на сокет который требуется закрыть после
/// работы функции, может совпасть с pSocketToClose1.
/// \return SOCKET_ERROR (-1) в случае ошибки сокета,
/// ALLOCATION_ERROR (-9) в случае ошибки аллокации,
/// SUCCESSFUL (0) в случае успеха.
int Server(Args* pArgs, Request* pRequest, Matrix** ppMatrixA,
           Matrix** ppMatrixB, SocketHandle* pSocketToClose1,
           SocketHandle* pSocketToClose2);

/// Устанавливает соеденение.
///
/// \param pArgs Указатель на аргумент коммандной строки.
/// \param pSocketToClose Указатель на сокет который требуется закрыть после
/// работы функции.
/// \return Сокет, готовый к приёму данных в случае успеха или
/// SOCKET_ERROR (-1) в случае ошибки сокета.
SocketHandle ServerConnect(Args* pArgs, SocketHandle* pSocketToClose);

/// Принимает запрос.
///
/// \param sock Сокет.
/// \param pRequest Указатель на запрос.
/// \return SOCKET_ERROR (-1) в случае ошибки сокета,
/// SUCCESSFUL (0) в случае успеха.
int ServerReceiveRequest(SocketHandle sock, Request* pRequest);

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
