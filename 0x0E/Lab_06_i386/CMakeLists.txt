cmake_minimum_required(VERSION 3.0)
project(Lab_06_i386 ASM)

set(CMAKE_ASM_FLAGS "-target i386")

add_executable(Lab_06_i386 main.s)
