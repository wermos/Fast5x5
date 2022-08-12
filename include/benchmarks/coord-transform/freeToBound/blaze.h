#ifndef FREE_TO_BOUND_BLAZE_H
#define FREE_TO_BOUND_BLAZE_H

#include "benchmark/benchmark.h"
#include "benchmarks/shared/common.hpp"
#include "blaze/Math.h"

template <typename T = float>
static void freeToBound_blaze(benchmark::State& state) {
    blaze::StaticMatrix<T, 6, 6, blaze::rowMajor> m1;
    blaze::StaticMatrix<T, 6, 8, blaze::rowMajor> m2, res;

    m1 = genRandomBlazeMat<T, 6, 6>();
    m2 = genRandomBlazeMat<T, 6, 8>();

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = m1 * m2;
    }
}

#endif  // FREE_TO_BOUND_BLAZE_H
