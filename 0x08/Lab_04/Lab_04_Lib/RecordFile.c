/// \file
/// \brief Реализация функций из RecordFile.h
/// \details Реализация функций из RecordFile.h.

#include <stdbool.h>

#include "RecordFile.h"
#include "Meta.h"
#include "IOWrapper.h"
#include "ReturnCodesLib.h"

int OpenRecordFile(char* path)
{
    int fd = OpenWrap(path, OPEN_FLAGS, READ_WRITE_MODE);

    return fd;
}

int CreateOrTruncateRecordFile(char* path, int recordSize)
{
    Meta meta;
    FillMeta(&meta, recordSize);

    int fd = OpenWrap(path, CREATE_TRUNCATE_FLAGS, READ_WRITE_MODE);

    RETURN_IF_NOT_SUCCESSFUL(WriteMeta(fd, &meta));
    //if (WriteMeta(fd, &meta) == FILE_UNSUCCESSFUL)
    //{
    //    return FILE_UNSUCCESSFUL;
    //}

    return fd;
}

int OpenOrCreateRecordFile(char* path, int recordSize)
{
    if (IsExistWritableReadableRecordFile(path))
    {
        return OpenRecordFile(path);
    }
    return CreateOrTruncateRecordFile(path, recordSize);
}

bool IsExistWritableReadableRecordFile(char* path)
{
    return AccessWrap(path, READ_WRITE_ACCESS) != FILE_UNSUCCESSFUL;
}

int CloseRecordFile(int fd)
{
    return CloseWrap(fd);
}

int SeekRecord(int fd, Meta* pMeta, int index)
{
    if (index == META_INDEX)
    {
        return LseekWrap(fd, 0, SEEK_SET);
    }
    if (pMeta == NULL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return LseekWrap(fd, sizeof(Meta) + index * pMeta->RecordSize, SEEK_SET);
}

int WriteRecord(int fd, Meta* pMeta, void* pRecord, int index)
{
    RETURN_IF_NOT_SUCCESSFUL(SeekRecord(fd, pMeta, index));
//    if (SeekRecord(fd, pMeta, index) == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }
    return WriteWrap(fd, pRecord, pMeta->RecordSize);
}

int ReadRecord(int fd, Meta* pMeta, void* pRecord, int index)
{
    RETURN_IF_NOT_SUCCESSFUL(SeekRecord(fd, pMeta, index));
//    if (SeekRecord(fd, pMeta, index) == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }
    return ReadWrap(fd, pRecord, pMeta->RecordSize);
}

int AddRecord(int fd, Meta* pMeta, void* pRecord)
{
    pMeta->Count++;
    RETURN_IF_NOT_SUCCESSFUL(WriteMeta(fd, pMeta));
//    if (WriteMeta(fd, pMeta) == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }
    return WriteRecord(fd, pMeta, pRecord, pMeta->Count - 1);
}

int WriteMeta(int fd, Meta* pMeta)
{
    RETURN_IF_NOT_SUCCESSFUL(SeekRecord(fd, pMeta, META_INDEX));
//    if (SeekRecord(fd, pMeta, META_INDEX) ==
//        FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }
    return WriteWrap(fd, pMeta, sizeof(Meta));
}

int ReadMeta(int fd, Meta* pMeta)
{
    RETURN_IF_NOT_SUCCESSFUL(SeekRecord(fd, pMeta, META_INDEX));
//    if (SeekRecord(fd, pMeta, META_INDEX) ==
//        FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }
    return ReadWrap(fd, pMeta, sizeof(Meta));
}

int ChangeSizeRecordFile(int fd, Meta* pMeta, int n)
{
    if (n > pMeta->Count)
    {
        return FILE_UNSUCCESSFUL;
    }
    return FtruncateWrap(fd, sizeof(Meta) + n * pMeta->RecordSize);
}

int RemoveRecordSwapWithLast(int fd, Meta* pMeta, int index)
{
    if (pMeta->Count > 1)
    {
        //char record[pMeta->RecordSize];
        void* pRecord = malloc(pMeta->RecordSize);
        if (pRecord == NULL)
        {
            return ALLOCATION_ERROR;
        }
        RETURN_IF_NOT_SUCCESSFUL(
                ReadRecord(fd, pMeta, pRecord, pMeta->Count - 1));
//        if (ReadRecord(fd, pMeta, pRecord, pMeta->Count - 1) ==
//            FILE_UNSUCCESSFUL)
//        {
//            return FILE_UNSUCCESSFUL;
//        }
        RETURN_IF_NOT_SUCCESSFUL(WriteRecord(fd, pMeta, pRecord, index));
//        if (WriteRecord(fd, pMeta, pRecord, index) ==
//            FILE_UNSUCCESSFUL)
//        {
//            return FILE_UNSUCCESSFUL;
//        }
        free(pRecord);
    }

    pMeta->Count--;
    RETURN_IF_NOT_SUCCESSFUL(WriteMeta(fd, pMeta));
//    if (WriteMeta(fd, pMeta) == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }

    return ChangeSizeRecordFile(fd, pMeta, pMeta->Count);
}

int RemoveRecordShift(int fd, Meta* pMeta, int index)
{
    if (pMeta->Count > 1)
    {
        int n = pMeta->Count - index - 1;
        //char records[pMeta->RecordSize * n];
        void* pRecords = malloc(pMeta->RecordSize * n);
        if (pRecords == NULL)
        {
            return FILE_UNSUCCESSFUL;
        }
        RETURN_IF_NOT_SUCCESSFUL(
                ReadRecords(fd, pMeta, pRecords, index + 1, n));
//        if (ReadRecords(fd, pMeta, pRecords, index + 1, n) ==
//            FILE_UNSUCCESSFUL)
//        {
//            return FILE_UNSUCCESSFUL;
//        }
        RETURN_IF_NOT_SUCCESSFUL(WriteRecords(fd, pMeta, pRecords, index, n));
//        if (WriteRecords(fd, pMeta, pRecords, index, n) ==
//            FILE_UNSUCCESSFUL)
//        {
//            return FILE_UNSUCCESSFUL;
//        }
        free(pRecords);
    }

    pMeta->Count--;
    RETURN_IF_NOT_SUCCESSFUL(WriteMeta(fd, pMeta));
//    if (WriteMeta(fd, pMeta) == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }

    return ChangeSizeRecordFile(fd, pMeta, pMeta->Count);
}

int ReadRecords(int fd, Meta* pMeta, void* pRecords, int index, int count)
{
    RETURN_IF_NOT_SUCCESSFUL(SeekRecord(fd, pMeta, index));
//    if (SeekRecord(fd, pMeta, index) == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }
    return ReadWrap(fd, pRecords, pMeta->RecordSize * count);
}

int WriteRecords(int fd,
                 Meta* pMeta,
                 void* pRecords,
                 int index,
                 int count)
{
    RETURN_IF_NOT_SUCCESSFUL(SeekRecord(fd, pMeta, index));
//    if (SeekRecord(fd, pMeta, index) == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }
    return WriteWrap(fd, pRecords, pMeta->RecordSize * count);
}

int DeleteRecordFile(char* path)
{
    return UnlinkWrap(path);
}

int CheckRecordFile(int fd, int recordSize)
{
    RETURN_IF_NOT_SUCCESSFUL(SeekRecord(fd, NULL, META_INDEX));
//    if (SeekRecord(fd, NULL, META_INDEX) == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }
    int actualVersion;
    RETURN_IF_NOT_SUCCESSFUL(ReadWrap(fd, &actualVersion, sizeof(uint32_t)));
//    if (ReadWrap(fd, &actualVersion, sizeof(uint32_t)) == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }
    if (actualVersion != META_VERSION)
    {
        return BAD_META;
    }
    Meta meta;
    RETURN_IF_NOT_SUCCESSFUL(ReadMeta(fd, &meta));
    if (meta.Version != META_VERSION ||
        meta.RecordSize != recordSize ||
        meta.MetaSize != sizeof(Meta))
    {
        return BAD_META;
    }
    return 0;
}
