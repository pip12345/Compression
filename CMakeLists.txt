cmake_minimum_required(VERSION 3.26) # The minimum CMake version used.
project(Compression) # Name of the current project.

add_executable(Compression) # Define a name for executable.

set(target Compression) # Create a name for target.

# Add the files  to add to executable.
target_sources(${target}
        PRIVATE
        main.cpp # The main file of the project.

        ./include/huff.h
        ./include/lzw.h

        ./src/huff.cpp
        ./src/lzw.cpp
)

include_directories(./include) # Instruct the compiler where to look for the given header files within this project.

target_compile_features(${target} PRIVATE cxx_std_20)