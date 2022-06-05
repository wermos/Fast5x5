file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp)

add_executable(benchmark ${SOURCES})

target_link_libraries(tests PUBLIC benchmark::benchmark PUBLIC xsimd)
target_include_directories(benchmark PUBLIC ../../libs/benchmark/include)
target_include_directories(benchmark PUBLIC ../../libs/xsimd/include)
