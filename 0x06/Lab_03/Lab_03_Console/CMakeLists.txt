cmake_minimum_required(VERSION 3.0)
project(Lab_03_Console C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fms-extensions")

#add_executable(Lab_03_Console main.c rar.c rar.h zip.c zip.h compressor_interface.h logging_compressor.h point2d.c point2d.h point3d.c point3d.h points.h points.c qwer.c qwer.h)

add_executable(Lab_03_Console qwer.c)

target_link_libraries(Lab_03_Console PUBLIC Lab_03_Lib)
