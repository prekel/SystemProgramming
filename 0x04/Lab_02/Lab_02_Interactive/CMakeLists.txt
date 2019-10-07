cmake_minimum_required(VERSION 3.10)
project(Lab_02_Interactive C)

set(CMAKE_C_STANDARD 11)

#if (UNIX)
#    if (NOT TARGET SDL2)
#        find_package(SDL2 REQUIRED)
#        include_directories(${SDL2_INCLUDE_DIRS})
#    endif (NOT TARGET SDL2)
#endif (UNIX)

add_executable(Lab_02_Interactive MainInteractive.c)

if (UNIX)
    target_link_libraries(Lab_02_Interactive PRIVATE SDL2main SDL2)
endif (UNIX)

if (MINGW)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mconsole -mwindows")
    target_link_libraries(Lab_02_Interactive PRIVATE mingw32)
endif (MINGW)

target_link_libraries(Lab_02_Interactive PRIVATE Lab_02_InteractiveLib)
target_link_libraries(Lab_02_Interactive PRIVATE Lab_02_Lib)
