cmake_minimum_required(VERSION 3.0)
project(Lab_06_C C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab_06_C main.c)

target_link_libraries(Lab_06_C PRIVATE Lab_06_C_Lib)
