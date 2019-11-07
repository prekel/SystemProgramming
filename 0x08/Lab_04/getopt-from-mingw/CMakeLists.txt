cmake_minimum_required(VERSION 3.0)
project(getopt-from-mingw C)

set(CMAKE_C_STANDARD 11)

add_library(getopt-from-mingw getopt.c getopt.h)

target_include_directories(getopt-from-mingw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
