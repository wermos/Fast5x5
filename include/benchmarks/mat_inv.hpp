#pragma once

#include "benchmark/benchmark.h"
#include "inversion/blaze.h"
#include "inversion/custom.h"
#include "inversion/eigen.h"
#include "inversion/fastor.h"

// 4x4 float matrix inversion
BENCHMARK(inversion_eigen<4, float>)
        ->Name("inversion_eigen_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(inversion_blaze<4, float>)
        ->Name("inversion_blaze_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(inversion_custom<4, float>)
        ->Name("inversion_custom_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(inversion_fastor<4, float>)
        ->Name("inversion_fastor_4x4_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);

// 6x6 float matrix inversion
BENCHMARK(inversion_eigen<6, float>)
        ->Name("inversion_eigen_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(inversion_blaze<6, float>)
        ->Name("inversion_blaze_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(inversion_custom<6, float>)
        ->Name("inversion_custom_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(inversion_fastor<6, float>)
        ->Name("inversion_fastor_6x6_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);

// 8x8 float matrix inversion
BENCHMARK(inversion_eigen<8, float>)
        ->Name("inversion_eigen_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(inversion_blaze<8, float>)
        ->Name("inversion_blaze_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(inversion_custom<8, float>)
        ->Name("inversion_custom_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(inversion_fastor<8, float>)
        ->Name("inversion_fastor_8x8_float")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);

// 4x4 float matrix inversion
BENCHMARK(inversion_eigen<4, double>)
        ->Name("inversion_eigen_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(inversion_blaze<4, double>)
        ->Name("inversion_blaze_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(inversion_custom<4, double>)
        ->Name("inversion_custom_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(inversion_fastor<4, double>)
        ->Name("inversion_fastor_4x4_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);

// 6x6 double matrix inversion
BENCHMARK(inversion_eigen<6, double>)
        ->Name("inversion_eigen_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(inversion_blaze<6, double>)
        ->Name("inversion_blaze_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
/*BENCHMARK(inversion_custom<6, double>)
        ->Name("inversion_custom_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);*/
BENCHMARK(inversion_fastor<6, double>)
        ->Name("inversion_fastor_6x6_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);

// 8x8 double matrix inversion
BENCHMARK(inversion_eigen<8, double>)
        ->Name("inversion_eigen_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
BENCHMARK(inversion_blaze<8, double>)
        ->Name("inversion_blaze_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
/*BENCHMARK(inversion_custom<8, double>)
        ->Name("inversion_custom_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);*/
BENCHMARK(inversion_fastor<8, double>)
        ->Name("inversion_fastor_8x8_double")
        ->Threads(1)
        ->Repetitions(repetitions)
        ->DisplayAggregatesOnly(true)
        ->UseRealTime()
		->ReportAggregatesOnly(true);
