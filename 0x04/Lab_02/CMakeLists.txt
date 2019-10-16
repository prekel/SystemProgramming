cmake_minimum_required(VERSION 3.0)
project(Lab_02)

set(CMAKE_C_STANDARD 11)

add_subdirectory(Lab_02_Lib)
add_subdirectory(Lab_02_InteractiveLib)

if (ANDROID)
    add_subdirectory(Lab_02_Android/app/jni)
else (ANDROID)
    add_subdirectory(Lab_02_Interactive)
endif (ANDROID)
