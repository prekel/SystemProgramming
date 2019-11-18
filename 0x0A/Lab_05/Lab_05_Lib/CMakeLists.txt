cmake_minimum_required(VERSION 3.0)
project(Lab_05_Lib C)

set(CMAKE_C_STANDARD 99)

add_library(Lab_05_Lib
        ReturnCodes.h
        ParseInt.h ParseInt.c
        Input.c Input.h ReturnCodes.c)

target_include_directories(Lab_05_Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
