#ifndef ARCHIPELAGO_H
#define ARCHIPELAGO_H

#include <stdint.h>

#include "Meta.h"

/// Длина строки названия архипелага.
#define ARCHIPELAGO_NAME_LENGTH 120

/// \struct Archipelago
///
/// Архипелаг.
typedef struct
{
    /// Название архипелага.
    char Name[ARCHIPELAGO_NAME_LENGTH];
    /// Кол-во островов.
    int32_t CountIslands;
    /// Кол-во обитаемых островов.
    int32_t CountInhabitedIslands;
} Archipelago;

/// Заполняет структуру архипелага заданными значениями.
///
/// \param pArchipelago Указатель на заполняемую структуру.
/// \param name Указатель на название архипелага.
/// \param countIslands Кол-во островов архипелага.
/// \param countInhabitedIslands Кол-во обитаемых островов архипелага.
/// \return BAD_VALUE в случае неверных значений, SUCCESSFUL в случае успеха.
int FillArchipelago(Archipelago* pArchipelago,
                    char* name,
                    int countIslands,
                    int countInhabitedIslands);

/// Проверяет структуру архипелага на правильность значений.
///
/// \param pArchipelago Указатель на структуру архипелага.
/// \return BAD_RECORD если знаечния неправильные, SUCCESSFUL если значения
/// правильные.
int VerifyArchipelago(Archipelago* pArchipelago);

/// Устанавливает имя архипелага.
///
/// \param pArchipelago Указатель на структуру архипелага.
/// \param name Указатель на имя.
/// \return BAD_RECORD если имя - нулевой указатель или строка нулевой длины,
/// длину строки в случае успеха
int SetName(Archipelago* pArchipelago, char* name);

/// Считывает структуру архипелага из файла с записями фиксированной длины.
///
/// \param fd Файловый дескриптор файла.
/// \param pMeta Указатель на метаинформацию файла.
/// \param pArchipelago Указатель на структуру архипелага.
/// \param index Индекс записи в файле с записями.
/// \return Неотрицательное значение в случае успеха, один из кодов возврата
/// из ReturnCodesLib.h в случае неудачи.
int ReadArchipelago(int fd,
                    Meta* pMeta,
                    Archipelago* pArchipelago,
                    int index);

/// Записывает в файл с записями фиксированными длины структуру архипелелага.
///
/// \param fd Файловый дескриптор файла.
/// \param pMeta Указатель на метаинформацию файла.
/// \param pArchipelago Указатель на структуру архипелага.
/// \param index Индекс записи в файле с записями.
/// \return Неотрицательное значение в случае успеха, один из кодов возврата
/// из ReturnCodesLib.h в случае неудачи.
int WriteArchipelago(int fd,
                     Meta* pMeta,
                     Archipelago* pArchipelago,
                     int index);

/// Добавляет в файл с записями фиксированными длины структуру архипелелага.
///
/// \param fd Файловый дескриптор файла.
/// \param pMeta Указатель на метаинформацию файла.
/// \param pArchipelago Указатель на структуру архипелага.
/// \param index Индекс записи в файле с записями.
/// \return Неотрицательное значение в случае успеха, один из кодов возврата
/// из ReturnCodesLib.h в случае неудачи.
int AddArchipelago(int fd, Meta* pMeta, Archipelago* pArchipelago);

/// Возвращает индекс архипелага в файле с записями фиксированной длины с
/// заданным именем. Если архипелагов с таким именем несколько, возвращается
/// индекс архипелага с минимальным индексом.
///
/// \param fd Файловый дескриптор файла.
/// \param pMeta Указатель на метаинформацию файла.
/// \param name Название искомого архипелага.
/// \return Индекс искомого архиелага в случае успеха, один из кодов возврата
/// из ReturnCodesLib.h в случае неудачи. В частности NOT_FOUND если архипелаг
/// с таким именем отсутствует.
int IndexByName(int fd, Meta* pMeta, char* name);

/// Изменяет имя архипелага в файле с записями фиксированной длины.
///
/// \param fd Файловый дескриптор файла.
/// \param pMeta Указатель на метаинформацию файла.
/// \param index Индекс записи в файле с записями.
/// \param newName Новое имя архипелага.
/// \return Неотрицательное значение в случае успеха, один из кодов возврата
/// из ReturnCodesLib.h в случае неудачи.
int ModifyName(int fd, Meta* pMeta, int index, char* newName);

/// Изменяет кол-во островов архипелага в файле с записями фиксированной
/// длины.
///
/// \param fd Файловый дескриптор файла.
/// \param pMeta Указатель на метаинформацию файла.
/// \param index Индекс записи в файле с записями.
/// \param newCountIslands Новое кол-во островов.
/// \return Неотрицательное значение в случае успеха, один из кодов возврата
/// из ReturnCodesLib.h в случае неудачи.
int ModifyCountIslands(int fd, Meta* pMeta, int index, int newCountIslands);

/// Изменяет кол-во обитаемых островов архипелага в файле с записями
/// фиксированной длины.
///
/// \param fd Файловый дескриптор файла.
/// \param pMeta Указатель на метаинформацию файла.
/// \param index Индекс записи в файле с записями.
/// \param newCountInhabitedIslands Новое кол-во обитаемых островов.
/// \return Неотрицательное значение в случае успеха, один из кодов возврата
/// из ReturnCodesLib.h в случае неудачи.
int ModifyCountInhabitedIslands(int fd, Meta* pMeta, int index,
                                int newCountInhabitedIslands);

#endif //ARCHIPELAGO_H
