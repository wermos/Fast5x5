#ifndef INVERSION_CUSTOM_H
#define INVERSION_CUSTOM_H

#include "benchmark/benchmark.h"
#include "fast5x5/fast5x5.hpp"
#include "benchmarks/shared/common.hpp"

static void inversion_custom(benchmark::State& state) {
    using M = BaseMatrix<float, SIZE, SIZE>;

    M m1 = genRandomCustomSymMat<float, SIZE, SIZE>();
	M res;

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        Inverse<float, SIZE>::inverse(m1, res);
    }
}

#endif  // INVERSION_CUSTOM_H
