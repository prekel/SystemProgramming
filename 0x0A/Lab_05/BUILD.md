# Lab_05

## Сборка

Используется система сборки Autotools на Linux и CMake на Windows и Linux. Для сборки, вывода справки клиента и сервера требуется:

```shell script
# linux, autotools, make, gcc
./configure
make
./build/Lab_05_Client -h
./build/Lab_05_Server -h

# linux, autotools, make, clang
./configure CC=clang
make
./build/Lab_05_Client -h
./build/Lab_05_Server -h

# linux, cmake, make, gcc
mkdir buildcmake
cd buildcmake
cmake ..
make
./Lab_05_Client/Lab_05_Client -h
./Lab_05_Server/Lab_05_Server -h

# linux, cmake, make, clang
mkdir buildcmake
cd buildcmake
cmake -DCMAKE_C_COMPILER=clang ..
make
./Lab_05_Client/Lab_05_Client -h
./Lab_05_Server/Lab_05_Server -h

# windows, cmake, msbuild, msvc
mkdir buildcmake
cd buildcmake 
cmake -G "Visual Studio 16 2019" ..
msbuild .\ALL_BUILD.vcxproj
.\Lab_05_Client\Debug\Lab_05_Client.exe -h
.\Lab_05_Server\Debug\Lab_05_Server.exe -h

# windows, cmake, mingw32-make, mingw
mkdir buildcmake
cd buildcmake
cmake -G "MinGW Makefiles" ..
mingw32-make
.\Lab_05_Client\Lab_05_Client.exe -h
.\Lab_05_Server\Lab_05_Server.exe -h

# windows, cmake, mingw32-make, clang
mkdir buildcmake
cd buildcmake
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
mingw32-make
.\Lab_05_Client\Lab_05_Client.exe -h
.\Lab_05_Server\Lab_05_Server.exe -h

# windows, cmake, ninja, clang
mkdir buildcmake
cd buildcmake
cmake -G "Ninja" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_RC_COMPILER=llvm-rc ..
ninja
.\Lab_05_Client\Lab_05_Client.exe -h
.\Lab_05_Server\Lab_05_Server.exe -h
```
