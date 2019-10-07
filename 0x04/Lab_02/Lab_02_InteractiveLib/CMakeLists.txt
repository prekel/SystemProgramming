cmake_minimum_required(VERSION 3.0)
project(Lab_02_InteractiveLib C)

set(CMAKE_C_STANDARD 11)

add_library(Lab_02_InteractiveLib
        RendererThread.c RendererThread.h
        ProgramQuitThread.c ProgramQuitThread.h
        MainWindow.c MainWindow.h)

if (UNIX)
    if (TARGET SDL2)
        target_link_libraries(Lab_02_InteractiveLib PRIVATE SDL2main SDL2)
    else (TARGET SDL2)
        find_package(SDL2 REQUIRED)
        target_include_directories(
                Lab_02_InteractiveLib PRIVATE ${SDL2_INCLUDE_DIRS})
        target_link_libraries(Lab_02_InteractiveLib PRIVATE ${SDL2_LIBRARIES})
    endif (TARGET SDL2)
endif (UNIX)

if (MINGW)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mconsole -mwindows")
    target_link_libraries(Lab_02_InteractiveLib PRIVATE mingw32 SDL2main SDL2)
endif (MINGW)

target_link_libraries(Lab_02_InteractiveLib PRIVATE Lab_02_Lib)

target_include_directories(
        Lab_02_InteractiveLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
