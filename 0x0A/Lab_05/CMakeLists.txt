cmake_minimum_required(VERSION 3.0)
project(Lab_05)

set(CMAKE_C_STANDARD 99)

add_subdirectory(getopt-from-mingw)
add_subdirectory(Lab_05_Server)
add_subdirectory(Lab_05_Client)
add_subdirectory(Lab_05_Lib)
add_subdirectory(Lab_05_MatrixLib)
add_subdirectory(Lab_05_MatrixLibTests)
