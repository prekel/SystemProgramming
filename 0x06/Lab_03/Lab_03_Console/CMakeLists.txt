cmake_minimum_required(VERSION 3.0)
project(Lab_03_Console C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab_03_Console main.c rar.c rar.h zip.c zip.h compressor_interface.h logging_compressor.h point2d.c point2d.h)

target_link_libraries(Lab_03_Console PUBLIC Lab_02_Lib)
