#pragma once

#include "benchmark/benchmark.h"
#include "benchmarks/shared/common.hpp"
#include "fast5x5/fast5x5.hpp"

template <typename T = float>
static void boundToFree_custom(benchmark::State& state) {
    using M1 = BaseMatrix<T, 6, 8>;
    using M2 = BaseMatrix<T, 8, 8>;

    M1 m1 = genRandomCustomMat<T, 6, 8>();
    M2 m2 = genRandomCustomMat<T, 8, 8>();
    M1 res;

    for (auto _ : state) {
		benchmark::DoNotOptimize(m1);
		benchmark::DoNotOptimize(m2);

        matrix_mul_m_m(m1, m2, res);

        benchmark::DoNotOptimize(res);
    }
}
