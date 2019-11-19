/// \file
/// \brief Запрос
/// \details Запрос, функция его заполнения, перевода в интернет-форму,
/// передачи, получения...

#ifndef REQUEST_H
#define REQUEST_H

#include <stdint.h>

#include "Matrix.h"

/// \struct Request
///
/// Запрос
typedef struct
{
    /// Первый индекс (строка)
    uint32_t FirstIndex;
    /// Второй индекс (ряд)
    uint32_t SecondIndex;
    /// Порядок матрицы
    uint32_t Count;
    /// Размер передаваемого массива с элементами матрицы
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
/// \param pMatrix Уазатель на матрицу.
/// \param firstIndex Первый индекс (строка).
/// \param secondIndex Второй индекс (ряд).
void FillRequest(Request* pRequest, Matrix* pMatrix, int firstIndex,
                 int secondIndex);

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
