cmake_minimum_required(VERSION 3.0)
project(Lab_03_LibTests C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab_03_LibTests main.c)

target_link_libraries(Lab_03_LibTests PRIVATE Lab_03_Lib)
