#pragma once

#include "benchmark/benchmark.h"

#include "gemm/blaze.h"
#include "gemm/custom.h"
#include "gemm/eigen.h"
#include "gemm/fastor.h"

BENCHMARK(gemm_eigen<4, float>)
        ->Name("gemm_eigen_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_eigen<6, float>)
        ->Name("gemm_eigen_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_eigen<8, float>)
        ->Name("gemm_eigen_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_eigen<4, double>)
        ->Name("gemm_eigen_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_eigen<6, double>)
        ->Name("gemm_eigen_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_eigen<8, double>)
        ->Name("gemm_eigen_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();

BENCHMARK(gemm_blaze<4, float>)
        ->Name("gemm_blaze_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_blaze<6, float>)
        ->Name("gemm_blaze_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_blaze<8, float>)
        ->Name("gemm_blaze_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_blaze<4, double>)
        ->Name("gemm_blaze_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_blaze<6, double>)
        ->Name("gemm_blaze_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_blaze<8, double>)
        ->Name("gemm_blaze_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();

BENCHMARK(gemm_custom<4, float>)
        ->Name("gemm_custom_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_custom<6, float>)
        ->Name("gemm_custom_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_custom<8, float>)
        ->Name("gemm_custom_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_custom<4, double>)
        ->Name("gemm_custom_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
/*BENCHMARK(gemm_custom<6, double>)
        ->Name("gemm_custom_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_custom<8, double>)
        ->Name("gemm_custom_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();*/

BENCHMARK(gemm_fastor<4, float>)
        ->Name("gemm_fastor_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_fastor<6, float>)
        ->Name("gemm_fastor_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_fastor<8, float>)
        ->Name("gemm_fastor_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_fastor<4, double>)
        ->Name("gemm_fastor_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_fastor<6, double>)
        ->Name("gemm_fastor_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
BENCHMARK(gemm_fastor<8, double>)
        ->Name("gemm_fastor_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
