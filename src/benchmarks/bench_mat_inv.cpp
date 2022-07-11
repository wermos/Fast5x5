#include "benchmark/benchmark.h"

#include "benchmarks/inversion_blaze.h"
#include "benchmarks/inversion_eigen.h"
#include "benchmarks/inversion_custom.h"

constexpr int repetitions = 20;

#define BENCHMARK_SUITE(x)            \
    BENCHMARK(x)                      \
        ->Threads(1)                  \
        ->Repetitions(repetitions)    \
        ->DisplayAggregatesOnly(true) \
        ->UseRealTime();

BENCHMARK_SUITE(inversion_eigen);

BENCHMARK_SUITE(inversion_blaze);

BENCHMARK_SUITE(inversion_custom);

BENCHMARK_MAIN();
