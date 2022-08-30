#ifndef BOUND_TO_FREE_BLAZE_H
#define BOUND_TO_FREE_BLAZE_H

#include "benchmark/benchmark.h"
#include "blaze/Math.h"
#include "benchmarks/shared/common.hpp"

static void boundToFree_blaze(benchmark::State& state) {
	blaze::StaticMatrix<float, 6, 8, blaze::rowMajor> m1, res;
	blaze::StaticMatrix<float, 8, 8, blaze::rowMajor> m2;

    m1 = genRandomBlazeMat<float, 6, 8>();
    m2 = genRandomBlazeMat<float, 8, 8>();

    for (auto _ : state) {
		benchmark::DoNotOptimize(m1);
		benchmark::DoNotOptimize(m2);

        res = m1 * m2;

        benchmark::DoNotOptimize(res);
    }
}

#endif // BOUND_TO_FREE_BLAZE_H 
