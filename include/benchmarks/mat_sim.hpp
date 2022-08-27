#ifndef MAT_SIM_HPP
#define MAT_SIM_HPP

#include "benchmark/benchmark.h"

#include "similarity/blaze.h"
#include "similarity/custom.h"
#include "similarity/eigen.h"
#include "similarity/fastor.h"

#define BENCHMARK_SUITE(x)            \
    BENCHMARK(x)                      \
        ->Threads(1)                  \
        ->Repetitions(repetitions)    \
        ->DisplayAggregatesOnly(true) \
        ->UseRealTime();

BENCHMARK_SUITE(similarity_eigen);

BENCHMARK_SUITE(similarity_blaze);

BENCHMARK_SUITE(similarity_fastor);

BENCHMARK_SUITE(similarity_custom);

#undef BENCHMARK_SUITE
// cleaning up macros

#endif // MAT_SIM_HPP
