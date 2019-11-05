#ifndef FILE_H
#define FILE_H

#include "Meta.h"

#define META_INDEX -1

int OpenFile1(char* path);

int CloseFile1(int fd);

int CreateFile1(char* path, size_t size);

int OpenOrCreateFile(char* path, size_t size);

bool IsExist(char* path);

int ReadMeta(int fd, Meta* meta);

int WriteMeta(int fd, Meta* meta);

off_t SeekToStartRecord(int fd, int n);

int WriteRecord(int fd, void* data, int n);

void ReadRecord(int fd, void* data, int n);

int AddRecord(int fd, void* data);

int ChangeSize(int fd, int n);

void RemoveSwapWithLast(int fd, int indexToRemove);

void RemoveShift(int fd, int index);

size_t GetFileSize1(int fd);

int ReadToEnd(int fd, void* allData);

int DeleteFile(char* path);

#endif //FILE_H
