cmake_minimum_required(VERSION 3.10)
project(Lab_02_Lib C)

set(CMAKE_C_STANDARD 11)

add_library(Lab_02_Lib
        Input.c Input.h
        Philosopher.c Philosopher.h
        Fork.c Fork.h
        Table.c Table.h
        Utils.c Utils.h
        RealTimeTableStateThread.c RealTimeTableStateThread.h
        PhilosopherEatingThread.c PhilosopherEatingThread.h
        AutoEatThread.c AutoEatThread.h
        Log.c Log.h
        EatingInterrupter.c EatingInterrupter.h
        PhilosophersWaiterThread.c PhilosophersWaiterThread.h)

if (MSVC)
    include_directories("C:/Users/vladislav/Projects/_foreign/pthreads-w32-2-9-1-release/Pre-built.2/include")
endif (MSVC)

if (NOT MSVC)
    target_link_libraries(Lab_02_Lib PRIVATE pthread)
endif (NOT MSVC)



target_link_libraries(Lab_02_Lib PRIVATE m)

target_include_directories(Lab_02_Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
