#ifndef BOUND_TO_FREE_CUSTOM_H 
#define BOUND_TO_FREE_CUSTOM_H

#include "benchmark/benchmark.h"
#include "fast5x5/fast5x5.hpp"
#include "benchmarks/shared/common.hpp"

static void boundToFree_custom(benchmark::State& state) {
	using M1 = BaseMatrix<float, 6, 8>;
	using M2 = BaseMatrix<float, 8, 8>;

    M1 m1 = genRandomCustomMat<float, 6, 8>();
    M2 m2 = genRandomCustomMat<float, 8, 8>();
    M1 res;

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        matrix_mul_m_m(m1, m2, res);
    }
}

#endif // BOUND_TO_FREE_CUSTOM_H
