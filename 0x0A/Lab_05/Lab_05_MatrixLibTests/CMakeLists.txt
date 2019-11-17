cmake_minimum_required(VERSION 3.0)
project(Lab_05_MatrixLibTests C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab_05_MatrixLibTests main.c)

target_link_libraries(Lab_05_MatrixLibTests PRIVATE Lab_05_MatrixLib)

target_link_libraries(Lab_05_MatrixLibTests PRIVATE cunit)
