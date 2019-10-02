cmake_minimum_required(VERSION 3.10)
project(Lab_02 C)

set(CMAKE_C_STANDARD 11)

#include_directories(Lab_02_Lib)

add_executable(Lab_02 main.c)

target_link_libraries(Lab_02 PRIVATE Lab_02_Lib)
