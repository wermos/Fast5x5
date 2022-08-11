#ifndef MAT_COORD_TRANSFORM_HPP
#define MAT_COORD_TRANSFORM_HPP

#include "benchmark/benchmark.h"

#include "benchmarks/coord-transform/boundToFree/blaze.h"
#include "benchmarks/coord-transform/boundToFree/custom.h"
#include "benchmarks/coord-transform/boundToFree/eigen.h"

#include "benchmarks/coord-transform/freeToBound/blaze.h"
#include "benchmarks/coord-transform/freeToBound/custom.h"
#include "benchmarks/coord-transform/freeToBound/eigen.h"

#define BENCHMARK_SUITE(x)            \
    BENCHMARK(x)                      \
        ->Threads(1)                  \
        ->Repetitions(repetitions)    \
        ->DisplayAggregatesOnly(true) \
        ->UseRealTime();

BENCHMARK_SUITE(boundToFree_eigen);

BENCHMARK_SUITE(boundToFree_blaze);

BENCHMARK_SUITE(boundToFree_custom);

BENCHMARK_SUITE(freeToBound_eigen);

BENCHMARK_SUITE(freeToBound_blaze);

BENCHMARK_SUITE(freeToBound_custom);

#undef BENCHMARK_SUITE
// cleaning up macros

#endif // MAT_COORD_TRANSFORM_HPP
