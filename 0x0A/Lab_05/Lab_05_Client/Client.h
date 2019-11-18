/// \file
/// \brief Клиент
/// \details Основная функция клиента.

#ifndef CLIENT_H
#define CLIENT_H

/// Главная функция клиента. Устанавливает соеденение, отсылает запрос,
/// отсылает матрицу, закрывает соеденение.
///
/// \param pArgs Указатель на аргументы коммандной строки.
/// \param pMatrix Указатель на матрицу.
/// \return SOCKET_ERROR (-1) в случае ошибки сокета,
/// ALLOCATION_ERROR (-9) в случае ошибки аллокации,
/// SUCCESSFUL (0) в случае успеха.
int Client(Args* pArgs, Matrix* pMatrix);

#endif //CLIENT_H
