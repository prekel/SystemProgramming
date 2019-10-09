cmake_minimum_required(VERSION 3.0)
project(Lab_03_Console C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab_03_Console main.c)

target_link_libraries(Lab_03_Console PUBLIC Lab_02_Lib)
