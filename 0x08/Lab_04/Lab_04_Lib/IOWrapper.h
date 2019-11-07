#ifndef IOWRAPPER_H
#define IOWRAPPER_H

#ifdef _MSC_VER
#define READ_WRITE_MODE _S_IREAD | _S_IWRITE
#define CREATE_TRUNCATE_FLAGS _O_RDWR | _O_CREAT | _O_TRUNC
#define OPEN_FLAGS _O_RDWR
#else
#define READ_WRITE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
#define CREATE_TRUNCATE_FLAGS O_RDWR | O_CREAT | O_TRUNC
#define OPEN_FLAGS O_RDWR
#endif

int Open1(char *path, int flags, int mode);

int Close1(int fd);

int Read1(int fd, void *buf, int size);

int Write1(int fd, void *buf, int size);

int Unlink1(char *path);

int Lseek1(int fd, int offset, int whence);

#endif //IOWRAPPER_H
