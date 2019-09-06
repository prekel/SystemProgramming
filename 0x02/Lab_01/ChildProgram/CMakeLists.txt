cmake_minimum_required(VERSION 3.10)
project(ChildProgram C)

set(CMAKE_C_STANDARD 11)

add_executable(ChildProgram main.c Matrix.c Matrix.h input.c input.h)