cmake_minimum_required(VERSION 3.4)

# Google Benchmark build flags
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
set(BENCHMARK_INSTALL_DOCS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)

# add Google Bencmark
add_subdirectory(libs/benchmark)

# Googletest build flags
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

# add Googletest 
add_subdirectory(libs/googletest)

# xsimd build flags
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_COMPILER_IS_GNUCXX)
	# this flag only works on Clang and GCC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()

set(BUILD_TESTS OFF CACHE BOOL "" FORCE)

# add xsimd
add_subdirectory(libs/xsimd)

# add Eigen
add_subdirectory(libs/eigen)

find_package(LAPACK REQUIRED)
find_package(BLAS REQUIRED)

#add Blaze
add_subdirectory(libs/blaze)

add_subdirectory(benchmarks)
add_subdirectory(test)
