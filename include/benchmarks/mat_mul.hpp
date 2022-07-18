#include "benchmark/benchmark.h"

#include "gemm_blaze.h"
#include "gemm_custom.h"
#include "gemm_eigen.h"
#include "gemm_simple.h"

#define BENCHMARK_SUITE(x)            \
    BENCHMARK(x)                      \
        ->Threads(1)                  \
        ->Repetitions(repetitions)    \
        ->DisplayAggregatesOnly(true) \
        ->UseRealTime();

BENCHMARK_SUITE(gemm_simple);

BENCHMARK_SUITE(gemm_eigen);

BENCHMARK_SUITE(gemm_blaze);

BENCHMARK_SUITE(gemm_custom);
