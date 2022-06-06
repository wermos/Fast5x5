#include "benchmark/benchmark.h"

#include "benchmarks/gemm_custom.h"
#include "benchmarks/gemm_eigen.h"
#include "benchmarks/gemm_simple.h"

BENCHMARK(gemm_simple)->DisplayAggregatesOnly(true);

BENCHMARK(gemm_eigen)->DisplayAggregatesOnly(true);

BENCHMARK(gemm_custom)->DisplayAggregatesOnly(true);

BENCHMARK_MAIN();
