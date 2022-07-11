#ifndef INVERSION_CUSTOM_H
#define INVERSION_CUSTOM_H

#include "benchmark/benchmark.h"
#include "fast5x5/fast5x5.hpp"
#include "gemm_header.h"

static void inversion_custom(benchmark::State& state) {
    alignas(256) float a[SIZE * SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - i; j++) {
            // filling the upper triangle
            a[i][j] = randomFloat(0, 100'000.0);
            a[j][i] = a[i][j];
        }
    }

    using M = BaseMatrix<float, SIZE, SIZE>;
    M m1(a), res;

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        Inverse<float, 8>::inverse(m1, res);
    }
}

#endif  // INVERSION_CUSTOM_H
