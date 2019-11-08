#ifndef IOWRAPPER_H
#define IOWRAPPER_H

#ifdef _MSC_VER

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>

#else

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#endif

#ifdef _MSC_VER

/// Режим открытия для записи и чтения
#define READ_WRITE_MODE (_S_IREAD | _S_IWRITE)
/// Флаги открытия для создания и очистки файла
#define CREATE_TRUNCATE_FLAGS (_O_RDWR | _O_CREAT | _O_TRUNC)
/// Флаги открытия файла
#define OPEN_FLAGS (_O_RDWR)
/// Флаг на проверку чтения и записи
#define READ_WRITE_ACCESS 06

#else

/// Режим открытия для записи и чтения
#define READ_WRITE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)
/// Флаги открытия для создания и очистки файла
#define CREATE_TRUNCATE_FLAGS (O_RDWR | O_CREAT | O_TRUNC)
/// Флаги открытия файла
#define OPEN_FLAGS (O_RDWR)
/// Флаг на проверку чтения и записи
#define READ_WRITE_ACCESS (F_OK | R_OK | W_OK)

#endif

/// Открывает файл. Обёртка над функцией _open() из MSVC или над open() в
/// другом случае.
///
/// \param path Путь до файла.
/// \param flags Флаги открытия файла.
/// \param mode Режим открытия файла.
/// \return Результат выполнения оборачиваемой функции (файловый дескриптор),
/// в частности -1 (FILE_UNSUCCESSFUL) в случае неудачи.
int OpenWrap(char* path, int flags, int mode);

/// Закрывает файл. Обёртка над функцией _close() из MSVC или над close() в
/// другом случае.
///
/// \param fd Файловый дескриптор.
/// \return Результат выполнения оборачиваемой функции,
/// в частности -1 (FILE_UNSUCCESSFUL) в случае неудачи.
int CloseWrap(int fd);

/// Считывает заданное количество байт из файла в буфер. Обёртка над функцией
/// _read() из MSVC или над read() в другом случае.
///
/// \param fd Файловый дескриптор.
/// \param pBuffer Указатель на буфер.
/// \param size Кол-во считываемых байт.
/// \return Результат выполнения оборачиваемой функции,
/// в частности -1 (FILE_UNSUCCESSFUL) в случае неудачи.
int ReadWrap(int fd, void* pBuffer, unsigned int size);

/// Записывает содержимое буфера заданного размера в файл. Обёртка над
/// функцией _write() из MSVC или над write() в другом случае.
///
/// \param fd Файловый дескриптор.
/// \param pBuffer Указатель на буфер.
/// \param size Размер содержимого буфера.
/// \return Результат выполнения оборачиваемой функции,
/// в частности -1 (FILE_UNSUCCESSFUL) в случае неудачи.
int WriteWrap(int fd, void* pBuffer, unsigned int size);

/// Обёртка над функцией _unlink() из MSVC или над unlink() в другом случае.
///
/// \param path Путь до файла.
/// \return Результат выполнения оборачиваемой функции,
/// в частности -1 (FILE_UNSUCCESSFUL) в случае неудачи.
int UnlinkWrap(char* path);

/// Обёртка над функцией _lseek() из MSVC или над lseek() в другом случае.
///
/// \param fd Файловый дескриптор.
/// \param offset Смещение.
/// \param whence Относительно чего производится смещение (SEEK_SET или
/// SEEK_CUR или SEEK_END)
/// \return Результат выполнения оборачиваемой функции,
/// в частности -1 (FILE_UNSUCCESSFUL) в случае неудачи.
int LseekWrap(int fd, int offset, int whence);

/// Обрезает файл (изменяет размер). Обёртка над функцией _chsize() из MSVC
/// или над ftruncate() в другом случае.
///
/// \param fd Файловый дескриптор.
/// \param length Новый размер файла.
/// \return Результат выполнения оборачиваемой функции,
/// в частности -1 (FILE_UNSUCCESSFUL) в случае неудачи.
int FtruncateWrap(int fd, unsigned int length);

/// Проверяет права на запись и чтение файла. Обёртка над функцией _access()
/// из MSVC или над access() в другом случае.
///
/// \param path Путь до файла.
/// \param mode Проверяемый режим.
/// \return Результат выполнения оборачиваемой функции,
/// в частности -1 (FILE_UNSUCCESSFUL) в случае неудачи.
int AccessWrap(char* path, int mode);

#endif //IOWRAPPER_H
