cmake_minimum_required(VERSION 3.10)
project(ChildProgram C)

set(CMAKE_C_STANDARD 11)

add_executable(ChildProgram main.c Matrix.c Matrix.h Input.c Input.h
        MatrixTests.c MatrixTests.h Macro.h)

target_link_libraries(ChildProgram PRIVATE cunit)
