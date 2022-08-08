#ifndef SIMILARITY_BLAZE_H
#define SIMILARITY_BLAZE_H

#include "benchmark/benchmark.h"
#include "blaze/Math.h"
#include "benchmarks/shared/common.hpp"

static void similarity_blaze(benchmark::State& state) {
	blaze::StaticMatrix<float, SIZE, SIZE, blaze::rowMajor> m1, m2, res;

    m1 = genRandomBlazeMat<float, SIZE, SIZE>();
    m2 = genRandomBlazeMat<float, SIZE, SIZE>();

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = m1 * m2 * trans(m1);
    }
}

#endif // SIMILARITY_BLAZE_H
