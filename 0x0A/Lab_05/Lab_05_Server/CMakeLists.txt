cmake_minimum_required(VERSION 3.0)
project(Lab_05_Server C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab_05_Server main.c Server.c Server.h ServerArgs.c ServerArgs.h)

target_link_libraries(Lab_05_Server PRIVATE Lab_05_Lib)
target_link_libraries(Lab_05_Server PRIVATE Lab_05_MatrixLib)

if (WIN32 AND NOT MINGW)
target_link_libraries(Lab_05_Server PRIVATE getopt-from-mingw)
endif(WIN32 AND NOT MINGW)

if (WIN32)
    target_link_libraries(Lab_05_Server PRIVATE wsock32 ws2_32)
endif (WIN32)
