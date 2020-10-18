cmake_minimum_required(VERSION 3.13)
project(Lab_02_Wasm C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_EXECUTABLE_SUFFIX .html)

add_executable(Lab_02_Wasm main.c)

target_link_libraries(Lab_02_Wasm PRIVATE Lab_02_InteractiveLib)
target_link_libraries(Lab_02_Wasm PRIVATE Lab_02_Lib)
target_link_libraries(Lab_02_Wasm PRIVATE pthread rt m)

#target_link_options(Lab_02_Wasm PUBLIC "SHELL: --pre-js ${CMAKE_CURRENT_SOURCE_DIR}/prejs.js --js-library ${CMAKE_CURRENT_SOURCE_DIR}/jsLib.js")
#target_link_options(Lab_02_Wasm PUBLIC "SHELL: -s USE_GLFW=3 --preload-file glsl -s ALLOW_MEMORY_GROWTH=1")
target_link_options(Lab_02_Wasm PUBLIC "SHELL: -s USE_SDL=2")
target_link_options(Lab_02_Wasm PUBLIC "SHELL: -s LLD_REPORT_UNDEFINED")
target_link_options(Lab_02_Wasm PUBLIC "SHELL: -pthread")
target_link_options(Lab_02_Wasm PUBLIC "SHELL: -s INITIAL_MEMORY=268435456")

#target_link_options(Lab_02_Wasm PUBLIC "SHELL: --pre-js ${CMAKE_CURRENT_SOURCE_DIR}/scanf-hip.js --js-library ${CMAKE_CURRENT_SOURCE_DIR}/scanf-hip.js")
