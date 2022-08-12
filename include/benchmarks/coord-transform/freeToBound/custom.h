#pragma once

#include "benchmark/benchmark.h"
#include "benchmarks/shared/common.hpp"
#include "fast5x5/fast5x5.hpp"

template <typename T = float>
static void freeToBound_custom(benchmark::State& state) {
    using M1 = BaseMatrix<T, 6, 6>;
    using M2 = BaseMatrix<T, 6, 8>;

    M1 m1 = genRandomCustomMat<T, 6, 6>();
    M2 m2 = genRandomCustomMat<T, 6, 8>();
    M2 res;

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        matrix_mul_m_m(m1, m2, res);
    }
}