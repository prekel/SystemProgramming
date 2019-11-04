#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

#include "File.h"
#include "Meta.h"

int OpenFile(char* path)
{
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int fd = open(path, O_RDWR | O_CREAT, mode);

    assert(CheckMetaVersion(fd));

    return fd;
}

int CreateFile(char* path, size_t size)
{
    Meta meta;
    FillMeta(&meta, size);

    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, mode);

    WriteMeta(fd, &meta);

    return fd;
}

int OpenOrCreateFile(char* path, size_t size)
{
    if(IsExist(path))
    {
        return OpenFile(path);
    }
    return CreateFile(path, size);
}

bool IsExist(char* path)
{
    return access(path, F_OK | R_OK | W_OK) != -1;
}

int CloseFile(int fd)
{
    return close(fd);
}

int WriteMeta(int fd, Meta* meta)
{
    SeekToStartRecord(fd, -1);
    return write(fd, meta, sizeof(Meta));
}

int ReadMeta(int fd, Meta* meta)
{
    SeekToStartRecord(fd, -1);
    return read(fd, meta, sizeof(Meta));
}

off_t SeekToStartRecord(int fd, int n)
{
    if (n == -1)
    {
        return lseek(fd, 0, SEEK_SET);
    }

    Meta meta;
    ReadMeta(fd, &meta);
    return lseek(fd, sizeof(meta) + n * meta.Size, SEEK_SET);
}

int WriteRecord(int fd, void* data, int n)
{
    Meta meta;
    ReadMeta(fd, &meta);

    SeekToStartRecord(fd, n);
    return write(fd, data, meta.Size);
}

void ReadRecord(int fd, void* data, int n)
{
    Meta meta;
    ReadMeta(fd, &meta);

    SeekToStartRecord(fd, n);
    read(fd, data, meta.Size);
}

int AddRecord(int fd, void* data)
{
    Meta meta;
    ReadMeta(fd, &meta);
    meta.Count++;
    WriteMeta(fd, &meta);

    return WriteRecord(fd, data, meta.Count - 1);
}

int ChangeSize(int fd, int n)
{
    Meta meta;
    ReadMeta(fd, &meta);

    return ftruncate(fd, sizeof(Meta) + n * meta.Size);
}

void RemoveSwapWithLast(int fd, int indexToRemove, int indexToLast)
{
    Meta meta;
    ReadMeta(fd, &meta);
    meta.Count--;
    WriteMeta(fd, &meta);

    if (indexToLast > 0)
    {
        char data[meta.Size];
        ReadRecord(fd, &data, indexToLast);
        WriteRecord(fd, &data, indexToRemove);
    }

    ChangeSize(fd, indexToLast);
}

size_t GetFileSize(int fd)
{
    Meta meta;
    ReadMeta(fd, &meta);
    return sizeof(Meta) + meta.Count * meta.Count;
}

int ReadToEnd(int fd, void* allData)
{
    SeekToStartRecord(fd, -1);
    return read(fd, allData, GetFileSize(fd));
}
