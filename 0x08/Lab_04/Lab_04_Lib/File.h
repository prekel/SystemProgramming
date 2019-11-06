#ifndef FILE_H
#define FILE_H

#include "Meta.h"

#define READ_WRITE_UNSUCCESSFUL -1

int OpenFile1(char* path);

int CloseFile1(int fd);

int CreateFile1(char* path, size_t size);

int OpenOrCreateFile(char* path, size_t size);

bool IsExist(char* path);

off_t SeekToStartRecord(int fd, int n);

ssize_t WriteRecord(int fd, Meta* pMeta, void* data, int n);

ssize_t ReadRecord(int fd, Meta* pMeta, void* data, int n);

ssize_t AddRecord(int fd, Meta* pMeta, void* data);

int ChangeSize(int fd, int n);

void RemoveSwapWithLast(int fd, Meta* pMeta, int indexToRemove);

void RemoveShift(int fd, Meta* pMeta, int index);

size_t GetFileSize1(int fd, Meta* pMeta);

ssize_t ReadToEnd(int fd, void* allData);

int DeleteFile(char* path);

#endif //FILE_H
