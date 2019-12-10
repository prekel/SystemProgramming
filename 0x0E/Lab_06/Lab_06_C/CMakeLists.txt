cmake_minimum_required(VERSION 3.0)

project(Lab_06_C C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab_06_C main.c
        Matrix.c
        MatrixIO.c)

target_include_directories(Lab_06_C PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)