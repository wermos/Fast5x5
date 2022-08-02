#ifndef GEMM_CUSTOM_H
#define GEMM_CUSTOM_H

#include "benchmark/benchmark.h"
#include "fast5x5/fast5x5.hpp"
#include "benchmarks/shared/common.hpp"

template<int SIZE = 8, typename T = float>
static void gemm_custom(benchmark::State& state) {
    using M = BaseMatrix<T, SIZE, SIZE>;

    M m1 = genRandomCustomMat<T, SIZE, SIZE>();
	M m2 = genRandomCustomMat<T, SIZE, SIZE>();
	M res;

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        matrix_mul_m_m(m1, m2, res);
    }
}

#endif  // GEMM_CUSTOM_H
