#ifndef GEMM_BLAZE_H
#define GEMM_BLAZE_H

#include "benchmark/benchmark.h"
#include "blaze/Math.h"
#include "benchmarks/shared/common.hpp"

static void gemm_blaze(benchmark::State& state) {
    blaze::StaticMatrix<float, SIZE, SIZE, blaze::rowMajor> m1, m2, res;

    m1 = genRandomBlazeMat<float, SIZE, SIZE>();
    m2 = genRandomBlazeMat<float, SIZE, SIZE>();

    for (auto _ : state) {
		benchmark::DoNotOptimize(m1);
		benchmark::DoNotOptimize(m2);

        res = m1 * m2;

        benchmark::DoNotOptimize(res);
    }
}

#endif // GEMM_BLAZE_H
