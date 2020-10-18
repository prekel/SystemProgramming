cmake_minimum_required(VERSION 3.13)
project(Lab_02_Wasm C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_EXECUTABLE_SUFFIX .html)

add_executable(Lab_02_Wasm Main.c)


#target_link_options(Lab_02_Wasm PUBLIC "SHELL: --pre-js ${CMAKE_CURRENT_SOURCE_DIR}/prejs.js --js-library ${CMAKE_CURRENT_SOURCE_DIR}/jsLib.js")
#target_link_options(Lab_02_Wasm PUBLIC "SHELL: -s USE_GLFW=3 --preload-file glsl -s ALLOW_MEMORY_GROWTH=1")
target_link_options(Lab_02_Wasm PUBLIC "SHELL: -s USE_SDL=2 -s USE_SDL_IMAGE=2")
