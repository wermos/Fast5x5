#pragma once

#include "benchmark/benchmark.h"
#include "fast5x5/fast5x5.hpp"
#include "benchmarks/shared/common.hpp"

template<int SIZE = 8, typename T = float>
static void similarity_custom(benchmark::State& state) {
	using M = BaseMatrix<T, SIZE, SIZE>;

    M m1 = genRandomCustomMat<T, SIZE, SIZE>();
    M m2 = genRandomCustomMat<T, SIZE, SIZE>();
    M res, temp;

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        matrix_mul_m_m(m1, m2, temp);
		matrix_mul_m_mt(temp, m1, res);
    }
}
