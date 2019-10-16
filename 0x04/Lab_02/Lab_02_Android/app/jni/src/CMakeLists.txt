cmake_minimum_required(VERSION 3.0)
project(Lab_02_Android)

add_library(Lab_02_Android SHARED MainAndroid.c)

target_link_libraries(Lab_02_Android SDL2main SDL2)

target_link_libraries(Lab_02_Android Lab_02_Lib)
target_link_libraries(Lab_02_Android Lab_02_InteractiveLib)
