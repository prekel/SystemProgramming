/// \file
/// \brief Метаинформация.
/// \details Метаинформация, её структура и функции.

#ifndef META_H
#define META_H

#include <stdbool.h>
#include <stdint.h>

/// Текущая версия файла (метаинформации).
#define META_VERSION 14
/// Индекс метаинформации для функции SeekRecord() итд.
#define META_INDEX (-1)

/// \struct Meta
///
/// Метаинформация.
typedef struct
{
    /// Версия файла.
    int32_t Version;
    /// Кол-во записей в файле.
    int32_t Count;
    /// Размер записи.
    uint32_t RecordSize;
    /// Размер метаинформации.
    uint32_t MetaSize;
} Meta;

/// Заполняет структуру метаинформацию значениями.
///
/// \param pMeta Указатель на метаинформцию.
/// \param recordSize Размер записи.
void FillMeta(Meta* pMeta, int recordSize);

#endif //META_H
