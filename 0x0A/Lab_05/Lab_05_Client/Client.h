/// \file
/// \brief Клиент
/// \details Основная функция клиента.

#ifndef CLIENT_H
#define CLIENT_H

/// Главная функция клиента. Устанавливает соеденение, отсылает запрос,
/// отсылает матрицу, закрывает соеденение.
///
/// \param pArgs Указатель на аргументы коммандной строки.
/// \param pMatrixA Указатель на матрицу.
/// \return SOCKET_ERROR (-1) в случае ошибки сокета,
/// ALLOCATION_ERROR (-9) в случае ошибки аллокации,
/// BAD_VALUE (-2) в случае неверных введёных значений,
/// SUCCESSFUL (0) в случае успеха.
int Client(Args* pArgs, Matrix* pMatrixA, Matrix* pMatrixB,
           SocketHandle* pSocketToClose);

#endif //CLIENT_H
