/// \file
/// \brief Запрос
/// \details Запрос, функция его заполнения, перевода в интернет-форму,
/// передачи, получения...

#ifndef REQUEST_H
#define REQUEST_H

#include <stdint.h>

#include "Matrix.h"

// Кол-во передаваемых матриц в задании
#define MATRICES_COUNT 2

/// \struct Request
///
/// Запрос
typedef struct
{
    /// Порядок матрицы
    uint32_t Degree;
    /// Кол-во передаваемых матриц
    uint32_t CountMatrices;
    /// Размер передаваемого массива с элементами матриц
    uint32_t MatrixDataSize;
} Request;

/// Переводит поля запроса из host в net-форму.
///
/// \param pRequest Указатель на запрос.
void HtoNRequest(Request* pRequest);

/// Переводит поля запроса из net в host-форму.
///
/// \param pRequest Указатель на запрос.
void NtoHRequest(Request* pRequest);

/// Заполняет поля запроса.
///
/// \param pRequest Указатель на запрос.
/// \param pMatrixA Указатель на первую матрицу.
/// \param pMatrixB Указатель на вторую матрицу.
void FillRequest(Request* pRequest, int degree, int count);

/// Отправляет запрос.
///
/// \param sock Сокет.
/// \param pRequest Указатель на запрос.
/// \return SOCKET_ERROR (-1) в случае ошибки сокета,
/// SUCCESSFUL (0) в случае успеха.
int SendRequest(SocketHandle sock, Request* pRequest);

/// Отправляет матрицу.
///
/// \param sock Сокет.
/// \param pRequest Указатель на запрос.
/// \param pMatrix Указатель на матрицу.
/// \return SOCKET_ERROR (-1) в случае ошибки сокета,
/// ALLOCATION_ERROR (-9) в случае ошибки аллокации,
/// SUCCESSFUL (0) в случае успеха.
int SendMatrix(SocketHandle sock, Request* pRequest, Matrix* pMatrix);

/// Принимает запрос.
///
/// \param sock Сокет.
/// \param pRequest Указатель на запрос.
/// \return SOCKET_ERROR (-1) в случае ошибки сокета,
/// SUCCESSFUL (0) в случае успеха.
int ReceiveRequest(SocketHandle sock, Request* pRequest);

/// Принимает матрицу.
///
/// \param sock Сокет.
/// \param pRequest Указатель на запрос.
/// \param pMatrix Указатель на матрицу.
/// \return SOCKET_ERROR (-1) в случае ошибки сокета,
/// ALLOCATION_ERROR (-9) в случае ошибки аллокации,
/// SUCCESSFUL (0) в случае успеха.
int ReceiveMatrix(SocketHandle sock, Request* pRequest, Matrix* pMatrix);

#endif //REQUEST_H
