cmake_minimum_required(VERSION 3.0)
project(Lab_05_MatrixLib C)

set(CMAKE_C_STANDARD 99)

add_library(Lab_05_MatrixLib
        Matrix.c Matrix.h)

target_include_directories(Lab_05_MatrixLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
