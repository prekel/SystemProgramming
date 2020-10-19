cmake_minimum_required(VERSION 3.13)
project(Lab_02_Wasm C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_EXECUTABLE_SUFFIX .html)

add_executable(Lab_02_Wasm MainWasm.c)

target_link_libraries(Lab_02_Wasm PRIVATE Lab_02_InteractiveLib)
target_link_libraries(Lab_02_Wasm PRIVATE Lab_02_Lib)
target_link_libraries(Lab_02_Wasm PRIVATE pthread)

target_link_options(Lab_02_Wasm PUBLIC "SHELL: -s USE_SDL=2")
target_link_options(Lab_02_Wasm PUBLIC "SHELL: -pthread")

#target_link_options(Lab_02_Wasm PUBLIC "SHELL: -s ALLOW_MEMORY_GROWTH=1")
target_link_options(Lab_02_Wasm PUBLIC "SHELL: -s INITIAL_MEMORY=268435456")
