cmake_minimum_required(VERSION 3.26)
project(Compression)

set(CMAKE_CXX_STANDARD 17)

add_executable(Compression main.cpp lzw.h lzw.cpp)
