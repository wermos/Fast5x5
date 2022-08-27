#ifndef MAT_INV_HPP
#define MAT_INV_HPP

#include "benchmark/benchmark.h"

#include "inversion/blaze.h"
#include "inversion/custom.h"
#include "inversion/eigen.h"
#include "inversion/fastor.h"

#define BENCHMARK_SUITE(x)            \
    BENCHMARK(x)                      \
        ->Threads(1)                  \
        ->Repetitions(repetitions)    \
        ->DisplayAggregatesOnly(true) \
        ->UseRealTime();

BENCHMARK_SUITE(inversion_eigen);

BENCHMARK_SUITE(inversion_blaze);

BENCHMARK_SUITE(inversion_fastor);

BENCHMARK_SUITE(inversion_custom);

#undef BENCHMARK_SUITE
// cleaning up macros

#endif // MAT_INV_HPP
