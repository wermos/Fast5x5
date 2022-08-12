#ifndef BOUND_TO_FREE_BLAZE_H
#define BOUND_TO_FREE_BLAZE_H

#include "benchmark/benchmark.h"
#include "benchmarks/shared/common.hpp"
#include "blaze/Math.h"

template <typename T = float>
static void boundToFree_blaze(benchmark::State& state) {
    blaze::StaticMatrix<T, 6, 8, blaze::rowMajor> m1, res;
    blaze::StaticMatrix<T, 8, 8, blaze::rowMajor> m2;

    m1 = genRandomBlazeMat<T, 6, 8>();
    m2 = genRandomBlazeMat<T, 8, 8>();

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = m1 * m2;
    }
}

#endif  // BOUND_TO_FREE_BLAZE_H
