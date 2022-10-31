#pragma once

#include "benchmark/benchmark.h"

#include "similarity/blaze.h"
#include "similarity/custom.h"
#include "similarity/eigen.h"
#include "similarity/fastor.h"

// 4x4 float matrix similarity transform
BENCHMARK(similarity_eigen<4, float>)
        ->Name("similarity_eigen_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(similarity_blaze<4, float>)
        ->Name("similarity_blaze_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(similarity_custom<4, float>)
        ->Name("similarity_custom_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(similarity_fastor<4, float>)
        ->Name("similarity_fastor_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);

// 6x6 float matrix similarity transform
BENCHMARK(similarity_eigen<6, float>)
        ->Name("similarity_eigen_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(similarity_blaze<6, float>)
        ->Name("similarity_blaze_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(similarity_custom<6, float>)
        ->Name("similarity_custom_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(similarity_fastor<6, float>)
        ->Name("similarity_fastor_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);

// 8x8 float matrix similarity transform
BENCHMARK(similarity_eigen<8, float>)
        ->Name("similarity_eigen_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(similarity_blaze<8, float>)
        ->Name("similarity_blaze_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(similarity_custom<8, float>)
        ->Name("similarity_custom_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(similarity_fastor<8, float>)
        ->Name("similarity_fastor_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);

// 4x4 double matrix similarity transform
BENCHMARK(similarity_eigen<4, double>)
        ->Name("similarity_eigen_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(similarity_blaze<4, double>)
        ->Name("similarity_blaze_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(similarity_custom<4, double>)
        ->Name("similarity_custom_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(similarity_fastor<4, double>)
        ->Name("similarity_fastor_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);

// 6x6 double matrix similarity transform
BENCHMARK(similarity_eigen<6, double>)
        ->Name("similarity_eigen_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(similarity_blaze<6, double>)
        ->Name("similarity_blaze_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
/*BENCHMARK(similarity_custom<6, double>)
        ->Name("similarity_custom_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
		->ReportAggregatesOnly(true);*/
BENCHMARK(similarity_fastor<6, double>)
        ->Name("similarity_fastor_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);

// 8x8 double matrix similarity transform
BENCHMARK(similarity_eigen<8, double>)
        ->Name("similarity_eigen_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(similarity_blaze<8, double>)
        ->Name("similarity_blaze_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
/*BENCHMARK(similarity_custom<8, double>)
        ->Name("similarity_custom_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime();
		->ReportAggregatesOnly(true);*/
BENCHMARK(similarity_fastor<8, double>)
        ->Name("similarity_fastor_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);

