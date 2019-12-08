cmake_minimum_required(VERSION 3.0)
project(Lab_06_C_Lib C)

set(CMAKE_C_STANDARD 99)

add_library(Lab_06_C_Lib Matrix.c)

target_include_directories(Lab_06_C_Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../)
