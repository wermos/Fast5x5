file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp)

add_executable(benchmarks ${SOURCES})

target_link_libraries(benchmarks PUBLIC benchmark::benchmark PUBLIC xsimd)
target_include_directories(benchmarks PUBLIC ../../include)
target_include_directories(benchmarks PUBLIC ../libs/benchmark/include)
target_include_directories(benchmarks PUBLIC ../libs/xsimd/include)
target_include_directories(benchmarks PUBLIC ../libs/eigen)
target_include_directories(benchmarks PUBLIC ../libs/blaze)
