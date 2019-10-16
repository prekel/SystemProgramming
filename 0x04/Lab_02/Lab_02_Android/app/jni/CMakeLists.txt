cmake_minimum_required(VERSION 3.0)
project(Lab_02_Android)

#armeabi-v7a requires cpufeatures library
#include(AndroidNdkModules)
#android_ndk_import_module_cpufeatures()


# SDL sources are in a subfolder named "SDL"
#add_subdirectory(SDL)
#add_subdirectory(../../../../../SDL-mirror)

# Compilation of companion libraries
#add_subdirectory(SDL_image)
#add_subdirectory(SDL_mixer)
#add_subdirectory(SDL_ttf)

# Your game and its CMakeLists.txt are in a subfolder named "src"
add_subdirectory(src)

