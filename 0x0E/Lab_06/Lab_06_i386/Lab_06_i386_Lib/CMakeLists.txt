cmake_minimum_required(VERSION 3.0)
project(Lab_06_i386_Lib ASM)

set(CMAKE_ASM_FLAGS "-target i386")

add_library(Lab_06_i386_Lib STATIC lib.s)
