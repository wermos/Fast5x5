#pragma once

#include "benchmark/benchmark.h"

#include "benchmarks/similarity/blaze.h"
#include "benchmarks/similarity/custom.h"
#include "benchmarks/similarity/eigen.h"

BENCHMARK(similarity_eigen<4, float>)
        ->Name("similarity_eigen_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(similarity_eigen<6, float>)
        ->Name("similarity_eigen_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(similarity_eigen<8, float>)
        ->Name("similarity_eigen_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(similarity_eigen<4, double>)
        ->Name("similarity_eigen_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(similarity_eigen<6, double>)
        ->Name("similarity_eigen_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(similarity_eigen<8, double>)
        ->Name("similarity_eigen_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();

BENCHMARK(similarity_blaze<4, float>)
        ->Name("similarity_blaze_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(similarity_blaze<6, float>)
        ->Name("similarity_blaze_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(similarity_blaze<8, float>)
        ->Name("similarity_blaze_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(similarity_blaze<4, double>)
        ->Name("similarity_blaze_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(similarity_blaze<6, double>)
        ->Name("similarity_blaze_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(similarity_blaze<8, double>)
        ->Name("similarity_blaze_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();

BENCHMARK(similarity_custom<4, float>)
        ->Name("similarity_custom_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(similarity_custom<6, float>)
        ->Name("similarity_custom_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(similarity_custom<8, float>)
        ->Name("similarity_custom_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(similarity_custom<4, double>)
        ->Name("similarity_custom_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
/*BENCHMARK(similarity_custom<6, double>)
        ->Name("similarity_custom_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(similarity_custom<8, double>)
        ->Name("similarity_custom_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();*/
