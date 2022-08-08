# gemm benchmarks
add_executable(gemm_benchmarks gemm_benchmark.cpp)

target_link_libraries(gemm_benchmarks PUBLIC benchmark::benchmark PUBLIC xsimd)

target_include_directories(gemm_benchmarks PUBLIC ../../include)
target_include_directories(gemm_benchmarks PUBLIC ../libs/benchmark/include)
target_include_directories(gemm_benchmarks PUBLIC ../libs/xsimd/include)
target_include_directories(gemm_benchmarks PUBLIC ../libs/eigen)
target_include_directories(gemm_benchmarks PUBLIC ../libs/blaze)

# inversion benchmarks
add_executable(inversion_benchmarks inversion_benchmark.cpp)

target_link_libraries(inversion_benchmarks PUBLIC benchmark::benchmark PUBLIC xsimd)
target_link_libraries(inversion_benchmarks PUBLIC LAPACK::LAPACK PUBLIC BLAS::BLAS)

target_include_directories(inversion_benchmarks PUBLIC ../../include)
target_include_directories(inversion_benchmarks PUBLIC ../libs/benchmark/include)
target_include_directories(inversion_benchmarks PUBLIC ../libs/xsimd/include)
target_include_directories(inversion_benchmarks PUBLIC ../libs/eigen)
target_include_directories(inversion_benchmarks PUBLIC ../libs/blaze)

# similarity benchmarks
add_executable(similarity_benchmarks similarity_benchmark.cpp)

target_link_libraries(similarity_benchmarks PUBLIC benchmark::benchmark PUBLIC xsimd)

target_include_directories(similarity_benchmarks PUBLIC ../../include)
target_include_directories(similarity_benchmarks PUBLIC ../libs/benchmark/include)
target_include_directories(similarity_benchmarks PUBLIC ../libs/xsimd/include)
target_include_directories(similarity_benchmarks PUBLIC ../libs/eigen)
target_include_directories(similarity_benchmarks PUBLIC ../libs/blaze)

# combined benchmarks
add_executable(combined_benchmarks combined_benchmark.cpp)

target_link_libraries(combined_benchmarks PUBLIC benchmark::benchmark PUBLIC xsimd)

target_include_directories(combined_benchmarks PUBLIC ../../include)
target_include_directories(combined_benchmarks PUBLIC ../libs/benchmark/include)
target_include_directories(combined_benchmarks PUBLIC ../libs/xsimd/include)
target_include_directories(combined_benchmarks PUBLIC ../libs/eigen)
target_include_directories(combined_benchmarks PUBLIC ../libs/blaze)
