#ifndef MAT_COORD_TRANSFORM_HPP
#define MAT_COORD_TRANSFORM_HPP

#include "benchmark/benchmark.h"

#include "coord-transform/boundToFree/blaze.h"
#include "coord-transform/boundToFree/custom.h"
#include "coord-transform/boundToFree/eigen.h"
#include "coord-transform/boundToFree/fastor.h"

#include "coord-transform/freeToBound/blaze.h"
#include "coord-transform/freeToBound/custom.h"
#include "coord-transform/freeToBound/eigen.h"
#include "coord-transform/freeToBound/fastor.h"

#define BENCHMARK_SUITE(x)            \
    BENCHMARK(x)                      \
        ->Threads(1)                  \
        ->Repetitions(repetitions)    \
        ->DisplayAggregatesOnly(true) \
        ->UseRealTime();

/* bound to free */
BENCHMARK_SUITE(boundToFree_eigen);

BENCHMARK_SUITE(boundToFree_blaze);

BENCHMARK_SUITE(boundToFree_fastor);

BENCHMARK_SUITE(boundToFree_custom);

/* free to bound */
BENCHMARK_SUITE(freeToBound_eigen);

BENCHMARK_SUITE(freeToBound_blaze);

BENCHMARK_SUITE(freeToBound_fastor);

BENCHMARK_SUITE(freeToBound_custom);

#undef BENCHMARK_SUITE
// cleaning up macros

#endif // MAT_COORD_TRANSFORM_HPP
