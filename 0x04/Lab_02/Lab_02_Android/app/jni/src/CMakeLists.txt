cmake_minimum_required(VERSION 3.0)
project(main)

add_library(main SHARED MainAndroid.c)

target_link_libraries(main SDL2main SDL2)

target_link_libraries(main Lab_02_Lib)
target_link_libraries(main Lab_02_InteractiveLib)
