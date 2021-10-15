# - Set Cmake requirements then declare project 
cmake_minimum_required(VERSION 3.2)
project(MPAGSCipher VERSION 0.1.0)

# - When Makedfiles are generated, output all command lines by default
set(CMAKE_VERBOSE_MAKEFILE ON)

# - Prevent vendor extensions to C++11
set(CMAKE_CXX_EXTENSIONS OFF)

# - Set the C++ Standard directly
set(CMAKE_CXX_STANDARD 14)

# - Declare the buil of mpags-cipher main program
add_executable(mpags-cipher 
    mpags-cipher.cpp
    MPAGSCipher/TransformChar.cpp
    MPAGSCipher/fileProcess.cpp
    MPAGSCipher/runCaesarCipher.cpp
    )

target_include_directories(mpags-cipher
    PRIVATE MPAGSCipher)

# - Use standard set of flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wshadow -pedantic")

target_compile_features(mpags-cipher
    PRIVATE cxx_auto_type cxx_range_for cxx_uniform_initialization)