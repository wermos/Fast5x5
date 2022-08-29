#ifndef SIMILARITY_CUSTOM_H 
#define SIMILARITY_CUSTOM_H

#include "benchmark/benchmark.h"
#include "fast5x5/fast5x5.hpp"
#include "benchmarks/shared/common.hpp"

static void similarity_custom(benchmark::State& state) {
	using M = BaseMatrix<float, SIZE, SIZE>;

    M m1 = genRandomCustomMat<float, SIZE, SIZE>();
    M m2 = genRandomCustomMat<float, SIZE, SIZE>();
    M res, temp;

    for (auto _ : state) {
		benchmark::DoNotOptimize(m1);
		benchmark::DoNotOptimize(m2);
        benchmark::DoNotOptimize(res);

        matrix_mul_m_m(m1, m2, temp);
		matrix_mul_m_mt(temp, m1, res);
    }
}

#endif // SIMILARITY_CUSTOM_H
