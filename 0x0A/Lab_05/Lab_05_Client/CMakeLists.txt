cmake_minimum_required(VERSION 3.0)
project(Lab_05_Client C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab_05_Client main.c Client.c Client.h)

target_link_libraries(Lab_05_Client PRIVATE Lab_05_Lib)
target_link_libraries(Lab_05_Client PRIVATE Lab_05_Net)

if (WIN32 AND NOT MINGW)
target_link_libraries(Lab_05_Client PRIVATE getopt-from-mingw)
endif(WIN32 AND NOT MINGW)

if (WIN32)
    target_link_libraries(Lab_05_Client PRIVATE wsock32 ws2_32)
endif (WIN32)
