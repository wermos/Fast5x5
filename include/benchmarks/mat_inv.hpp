#ifndef MAT_INV_HPP
#define MAT_INV_HPP

#include "benchmark/benchmark.h"

#include "shared/common.hpp"
#include "inversion/inversion_blaze.h"
#include "inversion/inversion_eigen.h"
#include "inversion/inversion_custom.h"

#define BENCHMARK_SUITE(x)            \
    BENCHMARK(x)                      \
        ->Threads(1)                  \
        ->Repetitions(repetitions)    \
        ->DisplayAggregatesOnly(true) \
        ->UseRealTime();

BENCHMARK_SUITE(inversion_eigen);

BENCHMARK_SUITE(inversion_blaze);

BENCHMARK_SUITE(inversion_custom);

#undef BENCHMARK_SUITE
// cleaning up macros

#endif // MAT_INV_HPP
