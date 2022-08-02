#ifndef GEMM_BLAZE_H
#define GEMM_BLAZE_H

#include "benchmark/benchmark.h"
#include "blaze/Math.h"
#include "benchmarks/shared/common.hpp"

template<unsigned long SIZE = 8UL, typename T = float>
static void gemm_blaze(benchmark::State& state) {
    blaze::StaticMatrix<T, SIZE, SIZE, blaze::rowMajor> m1, m2, res;

    m1 = genRandomBlazeMat<T, SIZE, SIZE>();
    m2 = genRandomBlazeMat<T, SIZE, SIZE>();

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = m1 * m2;
    }
}

#endif  // GEMM_BLAZE_H
