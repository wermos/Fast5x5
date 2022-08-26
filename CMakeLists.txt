cmake_minimum_required(VERSION 3.10)

# set the project name
project (Fast5x5)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# We need thread support
find_package(Threads REQUIRED)

# Setting up the external libraries
add_subdirectory(libs)

# Building the benchmarks and tests
add_subdirectory(src)

