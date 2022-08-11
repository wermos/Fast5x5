#ifndef FREE_TO_BOUND_BLAZE_H
#define FREE_TO_BOUND_BLAZE_H

#include "benchmark/benchmark.h"
#include "blaze/Math.h"
#include "benchmarks/shared/common.hpp"

static void freeToBound_blaze(benchmark::State& state) {
	blaze::StaticMatrix<float, 6, 6, blaze::rowMajor> m1;
	blaze::StaticMatrix<float, 6, 8, blaze::rowMajor> m2, res;

    m1 = genRandomBlazeMat<float, 6, 6>();
    m2 = genRandomBlazeMat<float, 6, 8>();

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = m1 * m2;
    }
}

#endif // FREE_TO_BOUND_BLAZE_H
