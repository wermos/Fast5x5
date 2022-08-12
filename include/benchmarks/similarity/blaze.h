#pragma once

#include "benchmark/benchmark.h"
#include "blaze/Math.h"
#include "benchmarks/shared/common.hpp"

template<unsigned long SIZE = 8UL, typename T = float>
static void similarity_blaze(benchmark::State& state) {
	blaze::StaticMatrix<T, SIZE, SIZE, blaze::rowMajor> m1, m2, res;

    m1 = genRandomBlazeMat<T, SIZE, SIZE>();
    m2 = genRandomBlazeMat<T, SIZE, SIZE>();

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = m1 * m2 * trans(m1);
    }
}
