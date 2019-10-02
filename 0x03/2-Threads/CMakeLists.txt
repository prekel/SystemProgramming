cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)

#project(cleanup C)
#add_executable(cleanup cleanup.c)
#target_link_libraries(cleanup PRIVATE pthread)

#project(critical-section C)
#add_executable(critical-section critical-section.c)
#target_link_libraries(critical-section PRIVATE pthread)

project(detached C)
add_executable(detached detached.c)
target_link_libraries(detached PRIVATE pthread)

project(primes C)
add_executable(primes primes.c)
target_link_libraries(primes PRIVATE pthread)

project(pthread-1 C)
add_executable(pthread-1 pthread-1.c)
target_link_libraries(pthread-1 PRIVATE pthread)

project(pthread-2 C)
add_executable(pthread-2 pthread-2.c)
target_link_libraries(pthread-2 PRIVATE pthread)

project(pthread-3 C)
add_executable(pthread-3 pthread-3.c)
target_link_libraries(pthread-3 PRIVATE pthread)

project(tsd C)
add_executable(tsd tsd.c)
target_link_libraries(tsd PRIVATE pthread)
