#include "benchmark/benchmark.h"

#include "benchmarks/gemm_simple.h"
#include "benchmarks/gemm_eigen.h"
#include "benchmarks/gemm_custom.h"

constexpr int repetitions = 20;

#define BENCHMARK_SUITE(x) BENCHMARK(x) \
	->Threads(1)->Threads(8)            \
	->Repetitions(repetitions)          \
    ->DisplayAggregatesOnly(true)       \
    ->UseRealTime();

BENCHMARK_SUITE(gemm_simple);

BENCHMARK_SUITE(gemm_eigen);

BENCHMARK_SUITE(gemm_custom);

BENCHMARK_MAIN();
