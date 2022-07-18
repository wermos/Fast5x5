#include "benchmark/benchmark.h"

#include "gemm_header.h"
//#include "inversion_blaze.h"
#include "inversion_eigen.h"
#include "inversion_custom.h"

#define BENCHMARK_SUITE(x)            \
    BENCHMARK(x)                      \
        ->Threads(1)                  \
        ->Repetitions(repetitions)    \
        ->DisplayAggregatesOnly(true) \
        ->UseRealTime();

BENCHMARK_SUITE(inversion_eigen);

//BENCHMARK_SUITE(inversion_blaze);

BENCHMARK_SUITE(inversion_custom);
