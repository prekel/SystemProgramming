#include <stdbool.h>

#include "File.h"
#include "Meta.h"
#include "IOWrapper.h"

int OpenFile1(char* path)
{
    int fd = OpenWrap(path, OPEN_FLAGS, READ_WRITE_MODE);

    return fd;
}

int CreateOrTruncateFile(char* path, int recordSize)
{
    Meta meta;
    FillMeta(&meta, recordSize);

    int fd = OpenWrap(path, CREATE_TRUNCATE_FLAGS, READ_WRITE_MODE);

    if (WriteMeta(fd, &meta) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    return fd;
}

int OpenOrCreateFile(char* path, int recordSize)
{
    if (IsExist(path))
    {
        return OpenFile1(path);
    }
    return CreateOrTruncateFile(path, recordSize);
}

bool IsExist(char* path)
{
    return AccessWrap(path, READ_WRITE_ACCESS) != FILE_UNSUCCESSFUL;
}

int CloseFile1(int fd)
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

int WriteRecord(int fd, Meta* pMeta, void* data, int index)
{
    if (SeekRecord(fd, pMeta, index) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return WriteWrap(fd, data, pMeta->RecordSize);
}

int ReadRecord(int fd, Meta* pMeta, void* data, int index)
{
    if (SeekRecord(fd, pMeta, index) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return ReadWrap(fd, data, pMeta->RecordSize);
}

int AddRecord(int fd, Meta* pMeta, void* data)
{
    pMeta->Count++;
    if (WriteMeta(fd, pMeta) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    return WriteRecord(fd, pMeta, data, pMeta->Count - 1);
}

int WriteMeta(int fd, Meta* pMeta)
{
    if (SeekRecord(fd, pMeta, META_INDEX) ==
        FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return WriteWrap(fd, pMeta, sizeof(Meta));
}

int ReadMeta(int fd, Meta* pMeta)
{
    if (SeekRecord(fd, pMeta, META_INDEX) ==
        FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return ReadWrap(fd, pMeta, sizeof(Meta));
}

int ChangeSize(int fd, Meta* pMeta, int n)
{
    return FtruncateWrap(fd, sizeof(Meta) + n * pMeta->RecordSize);
}

int RemoveSwapWithLast(int fd, Meta* pMeta, int index)
{
    if (pMeta->Count > 1)
    {
        char data[pMeta->RecordSize];
        if (ReadRecord(fd, pMeta, &data, pMeta->Count - 1) ==
            FILE_UNSUCCESSFUL)
        {
            return FILE_UNSUCCESSFUL;
        }
        if (WriteRecord(fd, pMeta, &data, index) ==
            FILE_UNSUCCESSFUL)
        {
            return FILE_UNSUCCESSFUL;
        }
    }

    pMeta->Count--;
    if (WriteMeta(fd, pMeta) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    return ChangeSize(fd, pMeta, pMeta->Count);
}

int RemoveShift(int fd, Meta* pMeta, int index)
{
    if (pMeta->Count > 1)
    {
        int n = pMeta->Count - index - 1;
        char dataShift[pMeta->RecordSize * n];
        if (ReadRecords(fd, pMeta, &dataShift, index + 1, n) ==
            FILE_UNSUCCESSFUL)
        {
            return FILE_UNSUCCESSFUL;
        }
        if (WriteRecords(fd, pMeta, &dataShift, index, n) ==
            FILE_UNSUCCESSFUL)
        {
            return FILE_UNSUCCESSFUL;
        }
    }

    pMeta->Count--;
    if (WriteMeta(fd, pMeta) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    return ChangeSize(fd, pMeta, pMeta->Count);
}

int ReadRecords(int fd, Meta* pMeta, void* pRecords, int index, int count)
{
    if (SeekRecord(fd, pMeta, index) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return ReadWrap(fd, pRecords, pMeta->RecordSize * count);
}

int WriteRecords(int fd,
                 Meta* pMeta,
                 void* pRecords,
                 int index,
                 int count)
{
    if (SeekRecord(fd, pMeta, index) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return WriteWrap(fd, pRecords, pMeta->RecordSize * count);
}

int DeleteFile(char* path)
{
    return UnlinkWrap(path);
}

int CheckMeta(int fd, int recordSize)
{
    if (SeekRecord(fd, NULL, META_INDEX) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    int actualVersion;
    if (ReadWrap(fd, &actualVersion, sizeof(uint32_t)) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    if (actualVersion != META_VERSION)
    {
        return BAD_META;
    }
    Meta meta;
    ReadMeta(fd, &meta);
    if (meta.Version != META_VERSION ||
        meta.RecordSize != recordSize ||
        meta.MetaSize != sizeof(Meta))
    {
        return BAD_META;
    }
    return 0;
}
