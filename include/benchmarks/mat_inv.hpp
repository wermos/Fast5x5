#pragma once

#include "benchmark/benchmark.h"

#include "inversion/blaze.h"
#include "inversion/eigen.h"
#include "inversion/custom.h"

BENCHMARK(inversion_eigen<4, float>)
        ->Name("inversion_eigen_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(inversion_eigen<6, float>)
        ->Name("inversion_eigen_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(inversion_eigen<8, float>)
        ->Name("inversion_eigen_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(inversion_eigen<4, double>)
        ->Name("inversion_eigen_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(inversion_eigen<6, double>)
        ->Name("inversion_eigen_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(inversion_eigen<8, double>)
        ->Name("inversion_eigen_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();

BENCHMARK(inversion_blaze<4, float>)
        ->Name("inversion_blaze_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(inversion_blaze<6, float>)
        ->Name("inversion_blaze_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(inversion_blaze<8, float>)
        ->Name("inversion_blaze_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(inversion_blaze<4, double>)
        ->Name("inversion_blaze_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(inversion_blaze<6, double>)
        ->Name("inversion_blaze_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(inversion_blaze<8, double>)
        ->Name("inversion_blaze_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();

BENCHMARK(inversion_custom<4, float>)
        ->Name("inversion_custom_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(inversion_custom<6, float>)
        ->Name("inversion_custom_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(inversion_custom<8, float>)
        ->Name("inversion_custom_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
/*BENCHMARK(inversion_custom<4, double>)
        ->Name("inversion_custom_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(inversion_custom<6, double>)
        ->Name("inversion_custom_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(inversion_custom<8, double>)
        ->Name("inversion_custom_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();*/