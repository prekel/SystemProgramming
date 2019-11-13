cmake_minimum_required(VERSION 3.0)
project(Lab_05_Server C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab_05_Server main.c)

target_link_libraries(Lab_05_Server PRIVATE Lab_04_Lib)
target_link_libraries(Lab_05_Server PRIVATE Lab_04_Sockets)

if (WIN32 AND NOT MINGW)
target_link_libraries(Lab_05_Server PRIVATE getopt-from-mingw)
endif(WIN32 AND NOT MINGW)
