/// \file
/// \brief Сообщение о последней ошибки
/// \details Сообщение о последней ошибки.

#ifndef LASTERRORMESSAGE_H
#define LASTERRORMESSAGE_H

/// Возвращает номер последней ошибки используя errno или WSAGetLastError().
///
/// \return Номер последней ошибки
int LastError();

/// Печатает сообщение последней ошибки.
void PrintLastErrorMessage();

/// Печатает сообщение определённой ошибки.
///
/// \param error Номер ошибки.
void PrintErrorMessage(int error);

#endif //LASTERRORMESSAGE_H
