#ifndef INVERSION_CUSTOM_H
#define INVERSION_CUSTOM_H

#include "benchmark/benchmark.h"
#include "fast5x5/fast5x5.hpp"
#include "benchmarks/shared/common.hpp"

template<unsigned long SIZE = 8UL, typename T = float>
static void inversion_custom(benchmark::State& state) {
    using M = BaseMatrix<T, SIZE, SIZE>;

    M m1 = genRandomCustomSymMat<T, SIZE, SIZE>();
	M res;

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        Inverse<T, SIZE>::inverse(m1, res);
    }
}

#endif  // INVERSION_CUSTOM_H
