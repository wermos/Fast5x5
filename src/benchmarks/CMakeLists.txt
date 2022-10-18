# gemm benchmarks
add_executable(gemm_benchmarks gemm_benchmark.cpp)

target_link_libraries(gemm_benchmarks PUBLIC benchmark::benchmark PUBLIC xsimd)

target_include_directories(gemm_benchmarks PUBLIC ../../include)
target_include_directories(gemm_benchmarks PUBLIC ../libs/benchmark/include)
target_include_directories(gemm_benchmarks PUBLIC ../libs/xsimd/include)
target_include_directories(gemm_benchmarks PUBLIC ../libs/eigen)
target_include_directories(gemm_benchmarks PUBLIC ../libs/blaze)
target_include_directories(gemm_benchmarks PUBLIC ../libs/Fastor)

# inversion benchmarks
add_executable(inversion_benchmarks inversion_benchmark.cpp)

target_link_libraries(inversion_benchmarks PUBLIC benchmark::benchmark PUBLIC xsimd)
target_link_libraries(inversion_benchmarks PUBLIC LAPACK::LAPACK PUBLIC BLAS::BLAS)

target_include_directories(inversion_benchmarks PUBLIC ../../include)
target_include_directories(inversion_benchmarks PUBLIC ../libs/benchmark/include)
target_include_directories(inversion_benchmarks PUBLIC ../libs/xsimd/include)
target_include_directories(inversion_benchmarks PUBLIC ../libs/eigen)
target_include_directories(inversion_benchmarks PUBLIC ../libs/blaze)
target_include_directories(inversion_benchmarks PUBLIC ../libs/Fastor)

# similarity benchmarks
add_executable(similarity_benchmarks similarity_benchmark.cpp)

target_link_libraries(similarity_benchmarks PUBLIC benchmark::benchmark PUBLIC xsimd)

target_include_directories(similarity_benchmarks PUBLIC ../../include)
target_include_directories(similarity_benchmarks PUBLIC ../libs/benchmark/include)
target_include_directories(similarity_benchmarks PUBLIC ../libs/xsimd/include)
target_include_directories(similarity_benchmarks PUBLIC ../libs/eigen)
target_include_directories(similarity_benchmarks PUBLIC ../libs/blaze)
target_include_directories(similarity_benchmarks PUBLIC ../libs/Fastor)

# coordinate transform benchmarks
add_executable(coord_transform_benchmarks coord_transform_benchmark.cpp)

target_link_libraries(coord_transform_benchmarks PUBLIC benchmark::benchmark PUBLIC xsimd)

target_include_directories(coord_transform_benchmarks PUBLIC ../../include)
target_include_directories(coord_transform_benchmarks PUBLIC ../libs/benchmark/include)
target_include_directories(coord_transform_benchmarks PUBLIC ../libs/xsimd/include)
target_include_directories(coord_transform_benchmarks PUBLIC ../libs/eigen)
target_include_directories(coord_transform_benchmarks PUBLIC ../libs/blaze)
target_include_directories(coord_transform_benchmarks PUBLIC ../libs/Fastor)

# combined benchmarks
add_executable(combined_benchmarks combined_benchmark.cpp)

target_link_libraries(combined_benchmarks PUBLIC benchmark::benchmark PUBLIC xsimd)
target_link_libraries(combined_benchmarks PUBLIC LAPACK::LAPACK PUBLIC BLAS::BLAS)

target_include_directories(combined_benchmarks PUBLIC ../../include)
target_include_directories(combined_benchmarks PUBLIC ../libs/benchmark/include)
target_include_directories(combined_benchmarks PUBLIC ../libs/xsimd/include)
target_include_directories(combined_benchmarks PUBLIC ../libs/eigen)
target_include_directories(combined_benchmarks PUBLIC ../libs/blaze)
target_include_directories(combined_benchmarks PUBLIC ../libs/Fastor)
