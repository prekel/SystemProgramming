cmake_minimum_required(VERSION 3.0)
project(Lab_05_Net C)

set(CMAKE_C_STANDARD 99)

add_library(Lab_05_Net
        Socket.c Socket.h
        Request.c Request.h)

target_link_libraries(Lab_05_Net PRIVATE Lab_05_Lib)

target_include_directories(Lab_05_Net PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
