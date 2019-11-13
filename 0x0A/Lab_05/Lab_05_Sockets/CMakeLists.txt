cmake_minimum_required(VERSION 3.0)
project(Lab_05_Sockets C)

set(CMAKE_C_STANDARD 99)

add_library(Lab_05_Sockets
        Socket.c Socket.h)

target_include_directories(Lab_05_Sockets PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
