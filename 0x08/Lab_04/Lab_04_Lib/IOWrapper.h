#ifndef IOWRAPPER_H
#define IOWRAPPER_H

#ifdef _MSC_VER
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>
#else
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#ifdef _MSC_VER
#define READ_WRITE_MODE (_S_IREAD | _S_IWRITE)
#define CREATE_TRUNCATE_FLAGS (_O_RDWR | _O_CREAT | _O_TRUNC)
#define OPEN_FLAGS (_O_RDWR)
#define READ_WRITE_ACCESS 06
#else
#define READ_WRITE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)
#define CREATE_TRUNCATE_FLAGS (O_RDWR | O_CREAT | O_TRUNC)
#define OPEN_FLAGS (O_RDWR)
#define READ_WRITE_ACCESS (F_OK | R_OK | W_OK)
#endif

int Open1(char *path, int flags, int mode);

int Close1(int fd);

int Read1(int fd, void *buf, unsigned int size);

int Write1(int fd, void *buf, unsigned size);

int Unlink1(char *path);

int Lseek1(int fd, unsigned int offset, int whence);

int Ftruncate1(int fd, unsigned int length);

int Access1(char* path, int mode);

#endif //IOWRAPPER_H
