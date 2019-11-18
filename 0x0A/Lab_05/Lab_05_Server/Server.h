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
/// \param ppMatrix Указатель на указатель на матрицу.
/// \return SOCKET_ERROR (-1) в случае ошибки сокета,
/// SUCCESSFUL (0) в случае успеха.
int Server(Args* pArgs, Request* pRequest, Matrix** ppMatrix);

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
int ServerReceiveRequest(SocketHandle sock, Request* pRequest);

/// Принимает матрицу.
///
/// \param sock Сокет.
/// \param pRequest Указатель на запрос.
/// \param pMatrix Указатель на матрицу.
/// \return SOCKET_ERROR (-1) в случае ошибки сокета,
/// SUCCESSFUL (0) в случае успеха.
int ServerReceiveMatrix(SocketHandle sock, Request* pRequest,
                        Matrix* pMatrix);

/// Закрывает соеденение.
///
/// \param sock Сокет.
/// \return SOCKET_ERROR (-1) в случае ошибки сокета,
/// SUCCESSFUL (0) в случае успеха.
int ServerClose(SocketHandle sock);

#endif //SERVER_H
