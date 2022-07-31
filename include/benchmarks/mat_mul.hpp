#ifndef MAT_MUL_HPP
#define MAT_MUL_HPP

#include "benchmark/benchmark.h"

#include "gemm/gemm_blaze.h"
#include "gemm/gemm_custom.h"
#include "gemm/gemm_eigen.h"
//#include "gemm/gemm_simple.h"

#define BENCHMARK_SUITE(x)            \
    BENCHMARK(x)                      \
        ->Threads(1)                  \
        ->Repetitions(repetitions)    \
        ->DisplayAggregatesOnly(true) \
        ->UseRealTime();

//BENCHMARK_SUITE(gemm_simple);

BENCHMARK_SUITE(gemm_eigen);

BENCHMARK_SUITE(gemm_blaze);

BENCHMARK_SUITE(gemm_custom);

#undef BENCHMARK_SUITE
// cleaning up macros

#endif // MAT_MUL_HPP
