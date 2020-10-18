cmake_minimum_required(VERSION 3.0)
project(Lab_02)

set(CMAKE_C_STANDARD 11)

add_subdirectory(Lab_02_Lib)

if (ANDROID)
    add_subdirectory(Lab_02_Android/app/jni)
else (ANDROID)
    if (EMSCRIPTEN)
        add_subdirectory(Lab_02_Wasm)
    else (EMSCRIPTEN)
        add_subdirectory(Lab_02_InteractiveLib)
        add_subdirectory(Lab_02_Interactive)
    endif (EMSCRIPTEN)
endif (ANDROID)
