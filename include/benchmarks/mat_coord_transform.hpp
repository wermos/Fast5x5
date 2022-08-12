#ifndef MAT_COORD_TRANSFORM_HPP
#define MAT_COORD_TRANSFORM_HPP

#include "benchmark/benchmark.h"
#include "benchmarks/coord-transform/boundToFree/blaze.h"
#include "benchmarks/coord-transform/boundToFree/custom.h"
#include "benchmarks/coord-transform/boundToFree/eigen.h"
#include "benchmarks/coord-transform/freeToBound/blaze.h"
#include "benchmarks/coord-transform/freeToBound/custom.h"
#include "benchmarks/coord-transform/freeToBound/eigen.h"

BENCHMARK(boundToFree_eigen<float>)
    ->Name("boundToFree_eigen_float")
    ->Threads(1)
    ->Repetitions(repetitions)
    ->DisplayAggregatesOnly(true)
    ->UseRealTime();
BENCHMARK(boundToFree_eigen<double>)
    ->Name("boundToFree_eigen_double")
    ->Threads(1)
    ->Repetitions(repetitions)
    ->DisplayAggregatesOnly(true)
    ->UseRealTime();
BENCHMARK(freeToBound_eigen<float>)
    ->Name("freeToBound_eigen_float")
    ->Threads(1)
    ->Repetitions(repetitions)
    ->DisplayAggregatesOnly(true)
    ->UseRealTime();
BENCHMARK(freeToBound_eigen<double>)
    ->Name("freeToBound_eigen_double")
    ->Threads(1)
    ->Repetitions(repetitions)
    ->DisplayAggregatesOnly(true)
    ->UseRealTime();

BENCHMARK(boundToFree_blaze<float>)
    ->Name("boundToFree_blaze_float")
    ->Threads(1)
    ->Repetitions(repetitions)
    ->DisplayAggregatesOnly(true)
    ->UseRealTime();
BENCHMARK(boundToFree_blaze<double>)
    ->Name("boundToFree_blaze_double")
    ->Threads(1)
    ->Repetitions(repetitions)
    ->DisplayAggregatesOnly(true)
    ->UseRealTime();
BENCHMARK(freeToBound_blaze<float>)
    ->Name("freeToBound_blaze_float")
    ->Threads(1)
    ->Repetitions(repetitions)
    ->DisplayAggregatesOnly(true)
    ->UseRealTime();
BENCHMARK(freeToBound_blaze<double>)
    ->Name("freeToBound_blaze_double")
    ->Threads(1)
    ->Repetitions(repetitions)
    ->DisplayAggregatesOnly(true)
    ->UseRealTime();

BENCHMARK(boundToFree_custom<float>)
    ->Name("boundToFree_custom_float")
    ->Threads(1)
    ->Repetitions(repetitions)
    ->DisplayAggregatesOnly(true)
    ->UseRealTime();
/*BENCHMARK(boundToFree_custom<double>)
        ->Name("boundToFree_custom_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();*/
BENCHMARK(freeToBound_custom<float>)
    ->Name("freeToBound_custom_float")
    ->Threads(1)
    ->Repetitions(repetitions)
    ->DisplayAggregatesOnly(true)
    ->UseRealTime();
/*BENCHMARK(freeToBound_custom<double>)
        ->Name("freeToBound_custom_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();*/

#undef BENCHMARK_SUITE
// cleaning up macros

#endif  // MAT_COORD_TRANSFORM_HPP
