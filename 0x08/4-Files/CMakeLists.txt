cmake_minimum_required(VERSION 3.0)
project(check-access C)
project(create-file C)
project(hexdump C)
project(listdir C)
project(lock-file C)
project(lseek-huge C)
project(print-symlink C)
project(timestamp C)
project(write-args C)

set(CMAKE_C_STANDARD 11)

add_executable(check-access check-access.c)

add_executable(create-file create-file.c)

add_executable(hexdump hexdump.c)

add_executable(listdir listdir.c)

add_executable(lock-file lock-file.c)

add_executable(lseek-huge lseek-huge.c)

add_executable(print-symlink print-symlink.c)

add_executable(timestamp timestamp.c)

add_executable(write-args write-args.c)
