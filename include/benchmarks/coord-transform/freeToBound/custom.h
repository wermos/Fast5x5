#ifndef FREE_TO_BOUND_CUSTOM_H 
#define FREE_TO_BOUND_CUSTOM_H

#include "benchmark/benchmark.h"
#include "fast5x5/fast5x5.hpp"
#include "benchmarks/shared/common.hpp"

static void freeToBound_custom(benchmark::State& state) {
	using M1 = BaseMatrix<float, 6, 6>;
	using M2 = BaseMatrix<float, 6, 8>;

    M1 m1 = genRandomCustomMat<float, 6, 6>();
    M2 m2 = genRandomCustomMat<float, 6, 8>();
    M2 res;

    for (auto _ : state) {
		benchmark::DoNotOptimize(m1);
		benchmark::DoNotOptimize(m2);
        benchmark::DoNotOptimize(res);

        matrix_mul_m_m(m1, m2, res);
    }
}

#endif // FREE_TO_BOUND_CUSTOM_H
